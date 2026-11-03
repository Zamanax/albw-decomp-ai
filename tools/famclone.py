#!/usr/bin/env python
"""Family clone: reuse one matched source for shape-identical unmatched functions.

  python tools/famclone.py [--apply] [--limit N] [--region LO-HI] [--json]

A *shape* is a function's instruction stream with branch displacements and every
word that points into the image (literal-pool entries, absolute addresses) masked,
so two functions with the same shape differ only in callees, globals and
constants. When one function of a shape is already matched honestly, its source is
compiled and checked against the other members: fn.py check compares the object's
best-matching symbol, so no text edit is needed (a rename is only cosmetic).

Dry run by default. --apply registers each candidate that prints RESULT: MATCH and
IDENTITY ... 0 MISMATCH, keeping the anchor's flags (falling back to the default
set, then to the /fpic and -O2 variants). Registration goes through
worklist.py register, which re-verifies at the final path.
"""
import argparse
import collections
import json
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402

ROOT = fn.ROOT
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
WORKLIST = os.path.join(ROOT, "tools", "worklist.py")


def words(a):
    s, e = fn.func_range(a)
    out = []
    for o in range(s, e, 4):
        w = fn.rd32(o)
        if (w & 0x0E000000) == 0x0A000000 or (w >> 25) == 0x7D:      # b / bl / blx imm
            out.append(("BR", w >> 24))
        elif fn.in_text(w) or fn.in_ro(w) or fn.in_data(w):           # points into the image
            out.append(("P",))
        else:
            out.append(w)
    return (e - s, tuple(out))


def flag_sets(base):
    out = [base, DEFAULT_FLAGS,
           base.replace("--apcs=/interwork", "--apcs=/fpic"),
           DEFAULT_FLAGS.replace("--apcs=/interwork", "--apcs=/fpic"),
           base.replace("-O3 -Otime", "-O2 -Otime"),
           DEFAULT_FLAGS.replace("-O3 -Otime", "-O2 -Otime")]
    seen, uniq = set(), []
    for f in out:
        if f not in seen:
            seen.add(f)
            uniq.append(f)
    return uniq


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--apply", action="store_true", help="register the matches")
    ap.add_argument("--limit", type=int, default=0, help="max candidates to test")
    ap.add_argument("--region", help="LO-HI hex range")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    lo, hi = (int(x, 16) for x in a.region.split("-")) if a.region else (None, None)

    status = json.load(open(os.path.join(ROOT, "functions.json")))
    cands = [int(l.split()[0], 16) for l in open(os.path.join(ROOT, "logs", "triage", "unindexed_candidate.txt"))]
    cands = [c for c in cands if "%08X" % c not in status]
    if lo is not None:
        cands = [c for c in cands if lo <= c < hi]

    anchors = {}
    for key, v in status.items():
        if v.get("status") != "honest" or not v.get("path"):
            continue
        if not os.path.isfile(os.path.join(ROOT, v["path"])):
            continue
        anchors.setdefault(words(int(key, 16)), []).append((key, v))

    by_shape = collections.OrderedDict()
    for c in cands:
        by_shape.setdefault(words(c), []).append(c)

    todo = []
    for k, members in by_shape.items():
        if k in anchors:
            todo += [(m, anchors[k][0]) for m in members]
    if a.limit:
        todo = todo[:a.limit]
    if not a.json:
        print("%d unmatched candidates share a shape with an honest match (%d shapes)" % (
            len(todo), len({k for k in by_shape if k in anchors})))

    got = []
    for cand, (akey, av) in todo:
        key = "%08X" % cand
        src = os.path.join(ROOT, av["path"])
        hit = None
        for flags in flag_sets(av.get("flags") or DEFAULT_FLAGS):
            r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", src,
                                "0x%08X" % cand, "--cc", av.get("cc", "4.1/b1049"), "--flags", flags],
                               capture_output=True, text=True)
            out = r.stdout
            if "RESULT: MATCH" in out and "0 MISMATCH" in out:
                hit = flags
                break
        if not a.json:
            print("%s <- %s  %s" % (key, akey, ("MATCH with " + hit) if hit else "no"))
        if not hit:
            continue
        if a.apply:
            r = subprocess.run([sys.executable, WORKLIST, "register", "0x%08X" % cand, "--src", src,
                                "--flags", hit], capture_output=True, text=True)
            if "%s -> honest" % key not in r.stdout:
                print("  register refused: " + (r.stdout.strip().splitlines() or [""])[0][:100])
                continue
        got.append({"addr": key, "anchor": akey, "flags": hit, "path": av["path"]})

    if a.json:
        print(json.dumps(got))
    else:
        print("%d %s" % (len(got), "registered" if a.apply else "would register"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
