#!/usr/bin/env python3
"""Callee-consistency check for `__attribute__((notailcall))`.

The attribute counts as honest only when it describes a property of the callee: the callee is
never tail-called (`b callee` from another function) anywhere in the game. Then a per-callee
declaration in the original headers is the plausible explanation, not per-call-site steering.

  python tools/notailcall.py check <src>...   # list each notailcall callee with its B/BL counts
  python tools/notailcall.py update           # rescan every honest source, rewrite the registry

The registry is `shared/construct_exceptions.json` -> "notailcall" -> "callees"
({addr: {"tail_calls": n, "bl_calls": m}}). tools/audit.py checks honest sources against it
offline (no code.bin needed). A callee must be named `func_XXXXXXXX` / `FUN_XXXXXXXX` so its
address is known; anything else is rejected.
"""
import bisect
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402  (loads code.bin)
from audit import (EXCEPTIONS, INCLUDES_NAMED_REG, NOTAILCALL_WORD,  # noqa: E402
                   notailcall_callees as callees)

ROOT = fn.ROOT


def branch_counts(addrs):
    """addr -> (tail_calls, bl_calls): B / BL words in .text targeting addr from another function."""
    starts = json.load(open(os.path.join(ROOT, "funcs.json")))["starts"]
    want = {int(a, 16) for a in addrs}
    out = {a: [0, 0] for a in want}
    words = struct.unpack_from("<%dI" % (fn.TS // 4), fn.CODE, 0)
    for i, w in enumerate(words):
        kind = w & 0x0F000000
        if (kind != 0x0A000000 and kind != 0x0B000000) or (w >> 28) == 0xF:
            continue
        imm = w & 0xFFFFFF
        imm = imm - 0x1000000 if imm & 0x800000 else imm
        src = fn.TA + i * 4
        t = src + 8 + (imm << 2)
        if t not in want or bisect.bisect_right(starts, src) == bisect.bisect_right(starts, t):
            continue  # a branch inside the callee itself is a loop, not a call
        out[t][0 if kind == 0x0A000000 else 1] += 1
    return {"%08X" % a: tuple(c) for a, c in out.items()}


def honest_sources():
    data = json.load(open(os.path.join(ROOT, "functions.json")))
    return sorted({e["path"] for e in data.values() if e.get("status") == "honest" and e.get("path")})


def cmd_check(paths):
    bad = 0
    for p in paths:
        found, unnamed = callees(open(p, errors="replace").read())
        counts = branch_counts(found)
        for a in sorted(found):
            tail, bl = counts[a]
            ok = tail == 0
            bad += not ok
            print("%s  %s  tail_calls=%d bl_calls=%d  %s" % (p, a, tail, bl, "ok" if ok else "INCONSISTENT"))
        for d in unnamed:
            bad += 1
            print("%s  UNNAMED callee (needs func_XXXXXXXX): %s" % (p, d))
    return 1 if bad else 0


def save_exceptions(ex):
    with open(EXCEPTIONS, "w") as fh:
        json.dump(ex, fh, indent=1, sort_keys=True)
        fh.write("\n")


def cmd_update():
    used = set()
    for p in honest_sources():
        used |= callees(open(os.path.join(ROOT, p), errors="replace").read())[0]
    counts = branch_counts(used)
    ex = json.load(open(EXCEPTIONS))
    ex["notailcall"]["callees"] = {a: {"tail_calls": c[0], "bl_calls": c[1]} for a, c in sorted(counts.items())}
    save_exceptions(ex)
    print("registry: %d callees, %d inconsistent" % (len(counts), sum(1 for c in counts.values() if c[0])))


def gate_and_log(key, text):
    """Registration gate for the conditionally honest constructs (called by worklist.py register).

    Returns a refusal reason, or None after logging `key` (8-hex address) under every construct the
    source uses, so shared/construct_exceptions.json and tools/audit.py stay in step.
    """
    uses_ntc = NOTAILCALL_WORD.search(text) is not None
    uses_reg = INCLUDES_NAMED_REG.search(text) is not None
    if not (uses_ntc or uses_reg):
        return None
    ex = json.load(open(EXCEPTIONS))
    if uses_ntc:
        found, unnamed = callees(text)
        if unnamed:
            return "notailcall callee without a func_XXXXXXXX name: %s" % unnamed[0][:80]
        counts = branch_counts(found)
        bad = sorted(a for a in found if counts[a][0])
        if bad:
            return "notailcall callee %s is tail-called %d times elsewhere (per-call-site steering)" % (
                bad[0], counts[bad[0]][0])
        for a in found:
            ex["notailcall"]["callees"][a] = {"tail_calls": 0, "bl_calls": counts[a][1]}
        ex["notailcall"]["entries"] = sorted(set(ex["notailcall"]["entries"]) | {key})
    if uses_reg:
        ex["named_register"]["entries"] = sorted(set(ex["named_register"]["entries"]) | {key})
    save_exceptions(ex)
    return None


def main():
    if len(sys.argv) >= 3 and sys.argv[1] == "check":
        sys.exit(cmd_check(sys.argv[2:]))
    if sys.argv[1:] == ["update"]:
        cmd_update()
        return
    sys.exit(__doc__)


if __name__ == "__main__":
    main()
