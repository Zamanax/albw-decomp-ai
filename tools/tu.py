#!/usr/bin/env python
"""Translation units: infer which functions were compiled together, and compile a target with them.

  uv run python tools/tu.py group 0xADDR            the inferred unit of ADDR, matched members marked
  uv run python tools/tu.py build 0xADDR SRC [--flags F]
                                                    SRC alone vs SRC inside its unit (scores both)
  uv run python tools/tu.py guards                  function-local static guards addressed from
                                                    another object (a unit-level anchor)

Why: some code depends on the rest of the file. armcc addresses a unit's data from one anchor, so a
function-local static's guard can be `[anchor, #4]` where the anchor is an earlier function's guard
(0x412F58 matched only beside 0x412BB4), and member-pointer constants load from a unit-wide table
(StateMgr init, docs/LESSONS.md). Compiling the function alone cannot produce either.

group: linkers lay out code, constant data and data in the same object order, and a unit's string
literals, constant tables and statics are referenced only by that unit's functions. Functions are
joined when they share such a private reference (one referenced only within 32 KB of code); every
function between two joined ones belongs to the same unit. Template and inline copies the linker
placed elsewhere are not joined (their references span more than 32 KB).

build: the members' registered sources are wrapped one per namespace (shared-header includes are
hoisted to the top, local includes made absolute) and added in address order, keeping only the ones
that still compile together; the target symbol is pinned with --sym. A matched member's own entry
re-verifies inside the combined file (checked on the 0x672xxx unit: 12/12).

Limit: namespaces keep every source's declarations apart, so an effect that needs two sources to
name the *same* global (anchoring on a TU global, not a function-local static) needs a hand-written
unit file. Measured on 310 unmatched functions with a best source and >= 3 matched neighbours: one
changed (0x412F58, now matched), the rest compiled identically.
"""
import argparse
import bisect
import collections
import json
import os
import re
import subprocess
import sys
import uuid

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402

ROOT = fn.ROOT
ARMCC = os.path.join(ROOT, "tools", "armcc", "4.1", "b1049", "bin", "armcc.exe")
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
WINDOW = 0x8000
SHARED = set(os.listdir(os.path.join(ROOT, "shared", "include")))
INCLUDE = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"].*$', re.M)
SKIP = ("excluded", "excluded_library", "interior_address")


def load():
    status = json.load(open(os.path.join(ROOT, "functions.json")))
    starts = sorted(set(json.load(open(os.path.join(ROOT, "funcs.json")))["starts"]))[:-1]
    skip = {int(k, 16) for k, v in status.items() if v.get("status") in SKIP}
    return status, [s for s in starts if s not in skip]


def pool_refs(a):
    """(ro words, data words) in the literal pool of the function at a."""
    s, e = fn.func_range(a)
    _, pool = fn.code_end(s, e)
    ro, da = set(), set()
    for x in pool:
        w = fn.rd32(x)
        if fn.in_ro(w):
            ro.add(w)
        elif fn.in_data(w):
            da.add(w)
    return ro, da


def units(starts):
    """{function: unit id} for every function inside an inferred unit."""
    users = collections.defaultdict(set)
    for a in starts:
        for w in set().union(*pool_refs(a)):
            users[w].add(a)
    parent = {a: a for a in starts}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for us in users.values():
        if 2 <= len(us) <= 40 and max(us) - min(us) <= WINDOW:
            us = sorted(us)
            for u in us[1:]:
                ra, rb = find(us[0]), find(u)
                if ra != rb:
                    parent[max(ra, rb)] = min(ra, rb)
    groups = collections.defaultdict(list)
    for a in starts:
        groups[find(a)].append(a)
    spans = []
    for lo, hi in sorted((min(v), max(v)) for v in groups.values() if len(v) > 1):
        if spans and lo <= spans[-1][1]:
            spans[-1][1] = max(spans[-1][1], hi)
        else:
            spans.append([lo, hi])
    out = {}
    for k, (lo, hi) in enumerate(spans):
        for a in starts[bisect.bisect_left(starts, lo):bisect.bisect_right(starts, hi)]:
            out[a] = k
    return out


def members(addr, status, starts):
    u = units(starts)
    if addr not in u:
        return []
    return [a for a in starts if u.get(a) == u[addr]]


def combine(parts):
    """One C++ file: shared includes hoisted, each part in its own namespace, address order."""
    incs, bodies = [], []
    for a, p in parts:
        text = open(p, encoding="utf-8", errors="replace").read()
        d = os.path.dirname(os.path.abspath(p))

        def rep(m):
            q, name = m.group(1), m.group(2)
            if q == "<" or name in SHARED:
                line = "#include %s%s%s" % (q, name, ">" if q == "<" else '"')
                if line not in incs:
                    incs.append(line)
                return ""
            return '#include "%s"' % os.path.join(d, name).replace("\\", "/")

        bodies.append("namespace tu_%08X {\n%s\n}\n" % (a, INCLUDE.sub(rep, text)))
    return "\n".join(incs) + "\n" + "\n".join(bodies)


def compiles(text, flags):
    tag = uuid.uuid4().hex[:10]
    src = os.path.join(ROOT, "logs", "tu", "_p_%s.cpp" % tag)
    obj = src[:-4] + ".o"
    os.makedirs(os.path.dirname(src), exist_ok=True)
    open(src, "w", encoding="utf-8").write(text)
    r = subprocess.run([ARMCC, "-c", "--cpp"] + flags.split() + ["-I", os.path.join(ROOT, "shared", "include"),
                                                                 "-o", obj, src], capture_output=True, text=True)
    for f in (src, obj):
        if os.path.exists(f):
            os.remove(f)
    return r.returncode == 0


def score(path, addr, flags):
    out = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", path, "0x%08X" % addr,
                          "--flags", flags, "--sym", "%08X" % addr], capture_output=True, text=True).stdout
    return "\n".join(l for l in out.splitlines() if l.startswith(("RESULT", "IDENTITY", "STRUCTURE:"))) or out[:300]


def cmd_group(a):
    status, starts = load()
    mem = members(a.addr, status, starts)
    if not mem:
        print("%08X: no unit inferred (no private reference shared with a neighbour)" % a.addr)
        return 1
    print("unit of %08X: %d functions, %08X-%08X" % (a.addr, len(mem), mem[0], mem[-1]))
    for x in mem:
        e = status.get("%08X" % x, {})
        print("  %08X %-8s %s" % (x, e.get("status", "-"), e.get("path", "")))
    return 0


def cmd_build(a):
    status, starts = load()
    flags = a.flags or DEFAULT_FLAGS
    if not a.src.endswith(".cpp"):
        print("build wraps sources in namespaces: the target source must be C++")
        return 1
    parts = [(a.addr, a.src)]
    seen = {os.path.normcase(os.path.abspath(a.src))}
    kept = list(parts)
    if not compiles(combine(kept), flags):
        print("the target source does not compile inside a namespace")
        return 1
    for x in members(a.addr, status, starts):
        e = status.get("%08X" % x, {})
        p = e.get("path", "")
        if x == a.addr or e.get("status") != "honest" or not p.endswith(".cpp") or not os.path.exists(os.path.join(ROOT, p)):
            continue
        p = os.path.join(ROOT, p)
        if os.path.normcase(os.path.abspath(p)) in seen:
            continue
        trial = sorted(kept + [(x, p)])
        if compiles(combine(trial), flags):
            kept = trial
            seen.add(os.path.normcase(os.path.abspath(p)))
    out = os.path.join(ROOT, "logs", "tu", "%08X_unit.cpp" % a.addr)
    open(out, "w", encoding="utf-8").write(combine(kept))
    print("alone:\n" + score(a.src, a.addr, flags))
    print("in unit (%d matched neighbours) -> %s:\n%s" % (len(kept) - 1, os.path.relpath(out, ROOT),
                                                          score(out, a.addr, flags)))
    return 0


def cmd_guards(a):
    status, starts = load()
    matched = {int(k, 16) for k, v in status.items() if v.get("status") in ("honest", "hack")}
    rows = []
    for x in starts:
        s, e = fn.func_range(x)
        lit = {}
        for y in range(s, min(e, s + 0x200), 4):
            ins = fn.dis1(y)
            if ins is None or ins.mnemonic != "ldr":
                continue
            m = fn._LIT.search(ins.op_str)
            if m:
                la = (y + 8 + fn._pcoff(m)) & ~3
                if fn.in_text(la) and fn.in_data(fn.rd32(la)):
                    lit[ins.op_str.split(",")[0]] = fn.rd32(la)
                continue
            m2 = re.match(r"(\w+), \[(\w+), #(0x[0-9a-f]+|\d+)\]$", ins.op_str)
            nxt = fn.dis1(y + 4)
            if m2 and m2.group(2) in lit and nxt is not None and nxt.mnemonic == "tst" and nxt.op_str.endswith("#1"):
                rows.append((x, lit[m2.group(2)], int(m2.group(3), 0)))
    print("%d guard tests addressed from another object" % len(rows))
    for x, d, k in rows:
        print("  %08X %-8s guard %08X = anchor %08X + %d" % (x, "matched" if x in matched else "", d + k, d, k))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("group")
    g.add_argument("addr", type=lambda v: int(v, 16))
    b = sub.add_parser("build")
    b.add_argument("addr", type=lambda v: int(v, 16))
    b.add_argument("src")
    b.add_argument("--flags")
    sub.add_parser("guards")
    a = ap.parse_args()
    return {"group": cmd_group, "build": cmd_build, "guards": cmd_guards}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
