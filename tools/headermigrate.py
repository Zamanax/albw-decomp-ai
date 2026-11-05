#!/usr/bin/env python3
"""Shared-header migration harness: replace a file-local struct definition with a shared header.

  python tools/headermigrate.py <Struct> <header.h> [--apply] [--jobs 16] [--limit N] [--paths a,b]

For every honest C++ source with a file-scope `struct <Struct> { ... };`, build a candidate where
that definition is replaced in place by `#include "<header.h>"` (resolved through
shared/include), then compile-check EVERY functions.json entry that points at the file with its
recorded flags. A file migrates only if all of them still print RESULT: MATCH and
IDENTITY ... 0 MISMATCH; otherwise it is left alone and the reason is logged.

Without --apply nothing in src/ changes (candidates are written next to the source as
__hm_<file> and removed). The per-file outcome goes to logs/headermigrate/<Struct>.jsonl:
  ok | compile_error | nomatch (with words) | identity
The share of `ok` measures how many independently matched functions agree with the header's
helper forms; the failures are the evidence for which forms the header still gets wrong.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
RESULT = re.compile(r"RESULT: (NO MATCH|MATCH)\s+(\d+)/(\d+) words")
IDENTITY = re.compile(r"IDENTITY: (\d+) verified, (\d+) unverifiable, (\d+) MISMATCH")


def find_definition(text, name):
    """(start, end) of the first file-scope `struct name { ... };`, or None."""
    for m in re.finditer(r"\bstruct\s+%s\s*\{" % re.escape(name), text):
        if brace_depth(text, m.start()) != 0:
            continue
        depth = 0
        for j in range(text.index("{", m.start()), len(text)):
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    end = j + 1
                    k = re.match(r"\s*;", text[end:])
                    return m.start(), end + (k.end() if k else 0)
    return None


def brace_depth(text, pos):
    """Brace depth at pos, ignoring // and /* */ comments and string literals (good enough)."""
    stripped = re.sub(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\])*\"", lambda m: " " * len(m.group(0)),
                      text[:pos], flags=re.S)
    return stripped.count("{") - stripped.count("}")


OWNER_FIELD = re.compile(r"\b(\w+)\s*\*\s*mOwner\s*;")


def candidate(text, name, header, template=None, renames=()):
    """The source with its local `struct name {...};` replaced by the shared header.

    template: the header defines `template<class T> struct <template>`; the owner class is read
    from the removed definition's `X* mOwner;` field and the file gets `typedef <template><X> name;`.
    renames: (regex, replacement) pairs applied to the rest of the file (member-name differences).
    """
    span = find_definition(text, name)
    if not span:
        return None
    s, e = span
    repl = '\n#include "%s"\n' % header
    if template:
        owner = OWNER_FIELD.search(text[s:e])
        if not owner:
            return None
        repl += "typedef %s<%s> %s;\n" % (template, owner.group(1), name)
    rest = text[e:]
    for pat, sub in renames:
        rest = re.sub(pat, sub, rest)
    return text[:s] + repl + rest


def check(path, key, flags):
    out = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", path, "0x" + key,
                          "flags", flags], capture_output=True, text=True, cwd=ROOT, timeout=300).stdout
    if "COMPILE ERROR" in out or "Error:" in out:
        err = next((l.strip() for l in out.splitlines() if "Error:" in l), "compile error")
        return "compile_error", err[:200]
    r, i = RESULT.search(out), IDENTITY.search(out)
    if not r:
        return "compile_error", (out.strip().splitlines() or ["no output"])[-1][:200]
    if r.group(1) != "MATCH":
        return "nomatch", "%s/%s words" % (r.group(2), r.group(3))
    if not i or int(i.group(3)):
        return "identity", (i.group(0) if i else "no IDENTITY line")
    return "ok", "%s/%s" % (r.group(2), r.group(3))


def try_file(path, entries, name, header, apply, template=None, renames=()):
    full = os.path.join(ROOT, path)
    text = open(full, encoding="utf-8", errors="replace").read()
    new = candidate(text, name, header, template, renames)
    if new is None:
        return dict(path=path, outcome="no_definition")
    d, f = os.path.split(full)
    tmp = os.path.join(d, "__hm_" + f)
    open(tmp, "w", encoding="utf-8").write(new)
    try:
        for key, ent in entries:
            outcome, detail = check(tmp, key, ent.get("flags") or DEFAULT_FLAGS)
            if outcome != "ok":
                return dict(path=path, outcome=outcome, addr=key, detail=detail)
    finally:
        os.remove(tmp)
    if apply:
        open(full, "w", encoding="utf-8").write(new)
    return dict(path=path, outcome="ok", entries=[k for k, _ in entries])


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("struct")
    ap.add_argument("header")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--jobs", type=int, default=16)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--paths", help="comma-separated repo paths to restrict to")
    ap.add_argument("--template", help="header defines template<class T> struct TEMPLATE; owner from mOwner")
    ap.add_argument("--rename", action="append", default=[], metavar="REGEX=REPL",
                    help="rewrite member names in the rest of the file (repeatable)")
    ap.add_argument("--log", help="log name under logs/headermigrate (default: the struct name)")
    a = ap.parse_args()
    renames = [tuple(r.split("=", 1)) for r in a.rename]

    data = json.load(open(os.path.join(ROOT, "functions.json")))
    by_path = {}
    for key, ent in sorted(data.items()):
        if ent.get("status") in ("honest", "hack") and ent.get("path"):
            by_path.setdefault(ent["path"], []).append((key, ent))
    pat = re.compile(r"\bstruct\s+%s\s*\{" % re.escape(a.struct))
    paths = sorted(p for p, es in by_path.items()
                   if p.endswith(".cpp") and any(e["status"] == "honest" for _, e in es)
                   and os.path.exists(os.path.join(ROOT, p))
                   and pat.search(open(os.path.join(ROOT, p), encoding="utf-8", errors="replace").read()))
    if a.paths:
        keep = set(a.paths.split(","))
        paths = [p for p in paths if p in keep]
    if a.limit:
        paths = paths[:a.limit]

    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda p: try_file(p, by_path[p], a.struct, a.header, a.apply, a.template, renames),
                          paths))

    os.makedirs(os.path.join(ROOT, "logs", "headermigrate"), exist_ok=True)
    with open(os.path.join(ROOT, "logs", "headermigrate", (a.log or a.struct) + ".jsonl"), "w") as fh:
        for r in res:
            fh.write(json.dumps(r) + "\n")
    counts = {}
    for r in res:
        counts[r["outcome"]] = counts.get(r["outcome"], 0) + 1
    print("%s -> %s: %d files %s%s" % (a.struct, a.header, len(res), json.dumps(counts, sort_keys=True),
                                       " (applied)" if a.apply else ""))


if __name__ == "__main__":
    main()
