#!/usr/bin/env python3
"""Re-verify every matched source that includes the given shared header(s), directly or through
another shared header.

  python tools/headercheck.py <header.h> [<header2.h> ...] [--jobs 16]

A shared header is only correct while every function built on it still matches: after any edit to
shared/include, run this for the edited header. Prints the failing entries (MATCH + IDENTITY 0
MISMATCH required) and exits 1 if there are any.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC_DIR = os.path.join(ROOT, "shared", "include")
INCLUDE = re.compile(r'#\s*include\s*[<"]([^">]+)[">]')


def includers(headers):
    """Header names (basenames) that pull in any of `headers`, transitively through shared/include."""
    graph = {}
    for root, _, files in os.walk(INC_DIR):
        for f in files:
            if f.endswith(".h"):
                text = open(os.path.join(root, f), encoding="utf-8", errors="replace").read()
                graph[f] = {os.path.basename(m) for m in INCLUDE.findall(text)}
    closure = set(headers)
    changed = True
    while changed:
        changed = False
        for h, deps in graph.items():
            if h not in closure and deps & closure:
                closure.add(h)
                changed = True
    return closure


def check(key, ent):
    out = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", ent["path"],
                          "0x" + key, "flags", ent["flags"]], capture_output=True, text=True, cwd=ROOT,
                         timeout=300).stdout
    return key, ("RESULT: MATCH" in out and re.search(r"IDENTITY: \d+ verified, \d+ unverifiable, 0 MISMATCH", out)
                 is not None), (out.strip().splitlines() or [""])[0 if "Error" in out else -1][:160]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("headers", nargs="+")
    ap.add_argument("--jobs", type=int, default=16)
    a = ap.parse_args()
    asked = {os.path.basename(h) for h in a.headers}
    names = includers(asked)
    data = json.load(open(os.path.join(ROOT, "functions.json")))
    ents = []
    for key, ent in sorted(data.items()):
        if ent.get("status") not in ("honest", "hack") or not ent.get("path"):
            continue
        p = os.path.join(ROOT, ent["path"])
        if not os.path.exists(p):
            continue
        incs = {os.path.basename(m) for m in INCLUDE.findall(open(p, encoding="utf-8", errors="replace").read())}
        if incs & names:
            ents.append((key, ent))
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda kv: check(*kv), ents))
    bad = [(k, d) for k, ok, d in res if not ok]
    print("%s (+ %d including headers): %d entries, %d failing" % (
        ",".join(a.headers), len(names) - len(asked), len(res), len(bad)))
    for k, d in bad:
        print("  FAIL %s %s" % (k, d))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
