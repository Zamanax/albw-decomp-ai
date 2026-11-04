"""Audit invariants of the published data, without code.bin or armcc.

  python tools/audit.py [--json]
  python tools/audit.py stats [--json]

Checks (all offline, all read-only):
  keys            functions.json keys are 8-digit uppercase hex, zero-padded
  schema          status is one of the six known values; honest/hack entries
                  carry path+cc; hack carries non-empty hack_reasons;
                  honest carries empty hack_reasons; every other status
                  carries no path
  paths           every recorded path exists inside the repo and is tracked
                  by git
  format          functions.json matches its canonical dump (indent=1,
                  sort_keys=True, every line lstripped) so future edits
                  produce minimal diffs
  hacks           honest sources contain none of the textually detectable
                  forbidden tricks (weak, __schedule_barrier, asm, perm_t,
                  32-bit no-op masks); hack_reasons use the known vocabulary
  crossref        every functions.json address is a known start in funcs.json
  exceptions      conditionally honest constructs (shared/construct_exceptions.json):
                  an honest source using `notailcall` or including cp15.h is listed
                  there; every notailcall callee is named func_XXXXXXXX and never
                  tail-called (registry from tools/notailcall.py update); cp15.h
                  holds nothing but named-register declarations

`stats` recomputes the README status table and hack-reason counts from
functions.json, so the README never needs hand-updating arithmetic again.
"""
import argparse
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

STATUSES = ("honest", "hack", "no_source", "excluded", "excluded_library", "interior_address")
MATCHED = ("honest", "hack")
REASONS = ("weak", "__schedule_barrier", "asm", "identical_arms", "perm_t",
           "dummy_local", "volatile_dummy", "nop_mask", "oob_local")

TRICK_PATTERNS = (
    ("weak", re.compile(r"__attribute__\s*\(\(\s*weak\s*\)\)|\b__weak\b")),
    ("__schedule_barrier", re.compile(r"__schedule_barrier")),
    ("asm", re.compile(r"\b(?:__)?asm\b")),
    ("perm_t", re.compile(r"\bperm_t\b")),
    ("nop_mask", re.compile(r"&\s*0[xX][fF]{8}\b|\&\s*0[fF]{8}\b")),
)

EXCEPTIONS = os.path.join(ROOT, "shared", "construct_exceptions.json")
NOTAILCALL_WORD = re.compile(r"\bnotailcall\b")
STATEMENT_END = re.compile(r"[;{}]")
NOTAILCALL_NAME = re.compile(r"\b(?:func|FUN)_([0-9A-Fa-f]{8})\s*\(")
NAMED_REG_LINE = re.compile(r'\Aregister\s+unsigned\s+int\s+\w+\s+__asm\("(?:cp15:\d+:c\d+:c\d+:\d+|fpscr)"\);')
INCLUDES_NAMED_REG = re.compile(r'#\s*include\s*[<"](?:[^">]*/)?cp15\.h[">]')


def notailcall_callees(text):
    """(callee addresses, unnamed declarations) of every notailcall declaration in a source.

    The declaration is the text between the nearest `;`/`{`/`}` on either side of the attribute
    (found by scanning outward, not by a backtracking regex: sources can be long single lines).
    """
    found, unnamed = set(), []
    for m in NOTAILCALL_WORD.finditer(text):
        start = max(text.rfind(c, 0, m.start()) for c in ";{}") + 1
        end_m = STATEMENT_END.search(text, m.end())
        d = text[start:end_m.start() if end_m else len(text)]
        n = NOTAILCALL_NAME.search(d)
        if n:
            found.add(n.group(1).upper())
        else:
            unnamed.append(" ".join(d.split()))
    return found, unnamed


def check_exceptions(data, errors, warnings):
    if not os.path.exists(EXCEPTIONS):
        return
    ex = json.load(open(EXCEPTIONS, encoding="utf-8"))
    ntc, nreg = ex["notailcall"], ex["named_register"]
    ntc_listed, reg_listed = set(ntc["entries"]), set(nreg["entries"])
    registry = ntc["callees"]
    used_ntc, used_reg = set(), set()
    for addr, ent in data.items():
        if ent.get("status") != "honest" or not ent.get("path"):
            continue
        try:
            text = open(os.path.join(ROOT, ent["path"]), encoding="utf-8", errors="replace").read()
        except OSError:
            continue  # reported by the hacks check
        if re.search(r"\bnotailcall\b", text):
            used_ntc.add(addr)
            if addr not in ntc_listed:
                errors.append("exceptions: %s uses notailcall but is not listed in %s" % (addr, EXCEPTIONS))
            found, unnamed = notailcall_callees(text)
            for d in unnamed:
                errors.append("exceptions: %s notailcall callee has no func_XXXXXXXX name: %s" % (addr, d[:80]))
            for c in sorted(found):
                info = registry.get(c)
                if info is None:
                    errors.append("exceptions: %s notailcall callee %s missing from the registry "
                                  "(run tools/notailcall.py update)" % (addr, c))
                elif info["tail_calls"]:
                    errors.append("exceptions: %s notailcall callee %s is tail-called %d times elsewhere: "
                                  "per-call-site steering, not honest" % (addr, c, info["tail_calls"]))
        if INCLUDES_NAMED_REG.search(text):
            used_reg.add(addr)
            if addr not in reg_listed:
                errors.append("exceptions: %s includes cp15.h but is not listed in %s" % (addr, EXCEPTIONS))
    for addr in sorted(ntc_listed - used_ntc):
        warnings.append("exceptions: %s is listed under notailcall but no honest source of it uses it" % addr)
    for addr in sorted(reg_listed - used_reg):
        warnings.append("exceptions: %s is listed under named_register but no honest source of it uses it" % addr)
    header = os.path.join(ROOT, nreg["header"])
    for n, line in enumerate(open(header, encoding="utf-8"), 1):
        if "__asm" in line and not NAMED_REG_LINE.match(line.strip()):
            errors.append("exceptions: %s:%d is not a named-register declaration: %s" % (nreg["header"], n, line.strip()))

HEX_KEY = re.compile(r"\A[0-9A-F]{8}\Z")


def canonical_bytes(data):
    return "\n".join(l.lstrip() for l in json.dumps(data, indent=1, sort_keys=True).splitlines())


def load():
    with open(os.path.join(ROOT, "functions.json"), encoding="utf-8") as fh:
        return json.load(fh)


def check_all():
    errors, warnings = [], []
    data = load()
    raw = open(os.path.join(ROOT, "functions.json"), encoding="utf-8").read()

    if raw != canonical_bytes(data):
        errors.append("format: functions.json is not in its canonical dump (indent=1, sort_keys=True, flat left margin)")

    starts = set(json.load(open(os.path.join(ROOT, "funcs.json")))["starts"])
    tracked = set(subprocess.run(
        ["git", "-C", ROOT, "ls-files"], capture_output=True, text=True,
        check=True).stdout.splitlines())

    for addr, ent in data.items():
        if not HEX_KEY.match(addr):
            errors.append("keys: %r is not an 8-digit uppercase hex key" % addr)
        status = ent.get("status")
        if status not in STATUSES:
            errors.append("schema: %s has unknown status %r" % (addr, status))
            continue
        if status != "interior_address" and int(addr, 16) not in starts:
            errors.append("crossref: %s is not a start in funcs.json" % addr)
        path = ent.get("path")
        if status in MATCHED:
            if not path:
                errors.append("schema: %s is %s but has no source path" % (addr, status))
            elif not ent.get("cc"):
                errors.append("schema: %s has a path but no cc" % addr)
        else:
            if path:
                errors.append("schema: %s is %s but carries a path" % (addr, status))
        if status == "hack" and not ent.get("hack_reasons"):
            errors.append("schema: %s is a hack with no hack_reasons" % addr)
        if status == "honest" and ent.get("hack_reasons"):
            errors.append("schema: %s is honest but lists hack_reasons %r" % (addr, ent["hack_reasons"]))
        for reason in ent.get("hack_reasons", []):
            if reason not in REASONS:
                warnings.append("hacks: %s uses unknown hack reason %r" % (addr, reason))
        if path:
            full = os.path.join(ROOT, path)
            if not os.path.isfile(full):
                errors.append("paths: %s -> %s does not exist" % (addr, path))
            elif path not in tracked:
                warnings.append("paths: %s -> %s is not tracked by git" % (addr, path))

    n_honest = sum(1 for v in data.values() if v.get("status") == "honest")
    for addr, ent in data.items():
        if ent.get("status") != "honest" or not ent.get("path"):
            continue
        try:
            with open(os.path.join(ROOT, ent["path"]), encoding="utf-8", errors="replace") as fh:
                text = fh.read()
        except OSError as exc:
            errors.append("hacks: %s -> %s unreadable: %s" % (addr, ent["path"], exc))
            continue
        for name, pat in TRICK_PATTERNS:
            if pat.search(text):
                errors.append("hacks: %s is honest but %s appears in %s" % (addr, name, ent["path"]))
    check_exceptions(data, errors, warnings)
    return data, errors, warnings, n_honest


def stats(data):
    from collections import Counter
    total = len(json.load(open(os.path.join(ROOT, "funcs.json")))["starts"])
    by_status = Counter(v.get("status") for v in data.values())
    matched_src = by_status["honest"] + by_status["hack"]
    reasons = Counter(r for v in data.values() if v.get("status") == "hack" for r in v.get("hack_reasons", []))
    return {
        "total_functions": total,
        "matched_source_included": matched_src,
        "matched_source_included_pct": round(100.0 * matched_src / total, 1),
        "honest": by_status["honest"],
        "honest_pct": round(100.0 * by_status["honest"] / total, 1),
        "hack": by_status["hack"],
        "hack_pct": round(100.0 * by_status["hack"] / total, 1),
        "no_source": by_status["no_source"],
        "excluded": by_status["excluded"],
        "excluded_library": by_status["excluded_library"],
        "interior_address": by_status["interior_address"],
        "hack_reasons": dict(sorted(reasons.items(), key=lambda kv: -kv[1])),
    }


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", nargs="?", choices=("check", "stats"), default="check")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    data = load()
    if args.mode == "stats":
        out = stats(data)
        if args.json:
            print(json.dumps(out, indent=1, sort_keys=True))
        else:
            print("Total functions in funcs.json: %d" % out["total_functions"])
            print("Matched, source included:      %d  (%.1f%%)" % (out["matched_source_included"], out["matched_source_included_pct"]))
            print("  honest:                      %d  (%.1f%%)" % (out["honest"], out["honest_pct"]))
            print("  hack:                        %d  (%.1f%%)" % (out["hack"], out["hack_pct"]))
            print("Matched earlier, no source:    %d" % out["no_source"])
            print("Non-redistributable 3rd-party:  %d" % out["excluded"])
            print("Prebuilt middleware/SDK:       %d" % out["excluded_library"])
            print("Interior addresses:            %d" % out["interior_address"])
            print("Hack reasons:")
            for name, cnt in out["hack_reasons"].items():
                print("  %-20s %d" % (name, cnt))
        return 0

    data, errors, warnings, n_honest = check_all()
    if args.json:
        print(json.dumps({
            "functions": len(data),
            "honest": n_honest,
            "errors": errors,
            "warnings": warnings,
        }, indent=1, sort_keys=True))
    else:
        print("Audited %d entries in functions.json" % len(data))
        for e in errors:
            print("ERROR  %s" % e)
        for w in warnings:
            print("WARN   %s" % w)
        print("RESULT: %s (%d error%s, %d warning%s)" % (
            "CLEAN" if not errors else "FAIL",
            len(errors), "" if len(errors) == 1 else "s",
            len(warnings), "" if len(warnings) == 1 else "s"))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
