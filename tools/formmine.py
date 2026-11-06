#!/usr/bin/env python
"""Mine missing shared-header forms from campaign misses.

  python tools/formmine.py [--rounds 3] [--top 15] [--min-misses 2]

For every MISS of the last N campaign rounds (plan_round*.json joined with the ledger), collect the
markers its target contains: out-of-line call targets (bl/b) and literal-pool values in ro (vtables,
constant objects). Each marker is then scored over the whole binary: how many functions contain it and
how many of those are matched. A marker that recent misses keep containing and whose users are mostly
unmatched points at a construct the shared headers lack: the sead audit found the string family that
way (its vtables' users 1-2% matched against ~67% overall).

Markers already listed in shared/reopen.json are flagged `reopened`. Miss notes that say a header
lacks something are listed as well, since agents often name the missing form outright.

Writes logs/campaign/forms.md and prints its table; `campaign.py harvest` prints the top lines.
"""
import argparse
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402

ROOT = fn.ROOT
CAMP = os.path.join(ROOT, "logs", "campaign")
MANUAL = os.path.join(ROOT, "logs", "manual")
OUT = os.path.join(CAMP, "forms.md")
LACKS = re.compile(r"[^.;\n]{0,80}(?:header|sead_\w+\.h|shared/include)[^.;\n]{0,60}"
                   r"(?:has no|lacks|is missing|missing|no such|doesn't have|does not have|without)[^.;\n]{0,100}"
                   r"|[^.;\n]{0,60}\bno (?:\w+ ){0,3}(?:type|form|ctor|constructor|overload) in [^.;\n]{0,80}", re.I)


def markers(addr):
    """(calls, ro literals) of the function starting at addr, both as sets of ints."""
    s, e = fn.func_range(addr)
    calls, lits = set(), set()
    for x in range(s, e, 4):
        w = fn.rd32(x)
        if (w & 0x0E000000) == 0x0A000000 and (w >> 28) != 0xF:
            imm = w & 0xFFFFFF
            t = x + 8 + ((imm - 0x1000000 if imm & 0x800000 else imm) << 2)
            if not (s <= t < e):
                calls.add(t)
        elif fn.in_ro(w):
            lits.add(w)
    return calls, lits


def reopen_markers():
    p = os.path.join(ROOT, "shared", "reopen.json")
    if not os.path.exists(p):
        return set()
    out = set()
    for k, f in json.load(open(p)).items():
        if k.startswith("_"):
            continue
        for key in ("words", "calls"):
            out |= {int(x, 16) for x in f.get(key, [])}
    return out


def recent_misses(rounds):
    led = [json.loads(l) for l in open(os.path.join(CAMP, "ledger.jsonl")) if l.strip()]
    last = max(e["round"] for e in led)
    return sorted({e["addr"] for e in led if e["round"] > last - rounds and e["outcome"] in ("MISS", "TIMEOUT")}), last


def note_of(addr):
    for f in ("REPORT.json", "REPORT.prev.json"):
        p = os.path.join(MANUAL, addr, f)
        if os.path.exists(p):
            try:
                r = json.load(open(p, errors="replace"))
            except ValueError:
                continue
            return " ".join(str(r.get(k, "")) for k in ("note", "summary", "remaining_diff", "key_findings"))
    return ""


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--rounds", type=int, default=3, help="misses of the last N rounds")
    ap.add_argument("--top", type=int, default=15)
    ap.add_argument("--min-misses", type=int, default=2, help="a marker must occur in at least this many misses")
    a = ap.parse_args()

    status = json.load(open(os.path.join(ROOT, "functions.json")))
    matched = {int(k, 16) for k, v in status.items() if v.get("status") in ("honest", "hack")}
    starts = json.load(open(os.path.join(ROOT, "funcs.json")))["starts"]
    # big functions match less often whatever they contain: a marker is judged against the match rate
    # expected for its users' sizes, not the global one (Vec3 helpers sit in big actor functions)
    size_b = lambda s: min(sum(fn.func_range(s)[1] - s > 4 * w for w in (20, 40, 80, 160, 320)), 5)
    by_size = collections.defaultdict(lambda: [0, 0])
    users = collections.defaultdict(lambda: [0, 0, 0.0])     # marker -> [functions, matched, sum of expected rates]
    user_b = {}
    for s in starts:
        b = user_b[s] = size_b(s)
        by_size[b][0] += 1
        by_size[b][1] += s in matched
    rate_b = {b: k / float(n) for b, (n, k) in by_size.items()}
    for s in starts:
        c, l = markers(s)
        for m in c | l:
            users[m][0] += 1
            users[m][1] += s in matched
            users[m][2] += rate_b[user_b[s]]
    base = len(matched & set(starts)) / float(len(starts))

    misses, last = recent_misses(a.rounds)
    cited = collections.defaultdict(list)
    for x in misses:
        c, l = markers(int(x, 16))
        for m in c | l:
            cited[m].append(x)
    reo = reopen_markers()
    rows = []
    for m, xs in cited.items():
        n, k, exp = users[m]
        if len(xs) < a.min_misses or n < 3:
            continue
        rate, exp = k / float(n), exp / n
        if rate >= 0.8 * exp:     # its users match about as often as functions of their size: no missing construct
            continue
        rows.append(dict(m=m, kind="call" if fn.in_text(m) else "ro", misses=len(xs), users=n,
                         unmatched=n - k, rate=rate, exp=exp, name=fn.name_of(m) or "", ex=xs[:5], reopened=m in reo))
    # unmatched reach, weighted by how far below the size-expected match rate its users are
    rows.sort(key=lambda r: -(r["unmatched"] * (1 - r["rate"] / r["exp"]) * min(r["misses"], 5)))

    notes = []
    for x in misses:
        for mt in LACKS.finditer(note_of(x)):
            notes.append((x, " ".join(mt.group(0).split())[:200]))

    out = ["# Form candidates from campaign misses (rounds %d-%d, %d misses)" % (last - a.rounds + 1, last, len(misses)),
           "", "Markers that recent misses contain and whose users match well below the rate expected for "
           "their sizes (overall %.0f%%). A high `unmatched` with a low `matched` against `expected` is a "
           "construct the shared headers likely lack: prove it on its out-of-line instance, merge it, add a "
           "shared/reopen.json entry." % (100 * base), "",
           "| marker | kind | name | misses | users | unmatched | matched | expected | example misses |",
           "|---|---|---|---|---|---|---|---|---|"]
    for r in rows[:a.top]:
        out.append("| %08X | %s | %s | %d | %d | %d | %.0f%%%s | %.0f%% | %s |" % (
            r["m"], r["kind"], r["name"].replace("|", "/")[:60], r["misses"], r["users"], r["unmatched"],
            100 * r["rate"], " (reopened)" if r["reopened"] else "", 100 * r["exp"], " ".join(r["ex"])))
    out += ["", "## Miss notes naming something a header lacks", ""]
    out += ["- %s: %s" % (x, n) for x, n in notes[:40]] or ["(none)"]
    open(OUT, "w", encoding="utf-8").write("\n".join(out) + "\n")
    print("\n".join(out[:6 + min(a.top, len(rows))]))
    print("(%d notes naming a missing header form) -> %s" % (len(notes), os.path.relpath(OUT, ROOT)))


if __name__ == "__main__":
    main()
