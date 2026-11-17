#!/usr/bin/env python
"""Mine instruction idioms that unmatched large functions share and no matched function contains.

  uv run python tools/idioms.py [--k 8] [--min-words 80] [--min-users 12] [--top 25]

formmine.py ranks out-of-line markers (callees, ro literals). An inline helper leaves no marker: its
body is copied into every caller. This tool looks for those copies. Every function becomes a
register-blind instruction stream (fn.py's structure tokens, with call targets and ro/text literal
values kept, since they name the helper); every k-instruction window is counted over unmatched
functions above --min-words and over matched functions. A window that many unmatched large
functions contain and (almost) no matched function does is an inline form nobody has written yet.
Overlapping windows are clustered by the functions that contain them.

For each cluster the report lists its reach, the named callees/literals inside it and the smallest
functions that contain it: those are where to prove the form (decomp-manual: shared header first,
then shared/reopen.json). Writes logs/campaign/idioms.md.
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
OUT = os.path.join(ROOT, "logs", "campaign", "idioms.md")
SKIP = ("excluded", "excluded_library", "interior_address")
ADDR_TOK = re.compile(r"(?:^(?:bl|b\w*) |=)([0-9A-F]{6,8})\b")


def tokens(a):
    """Register-blind instruction tokens of the function at a (code only, no literal pool)."""
    s, e = fn.func_range(a)
    ce = fn.code_end(s, e)[0]
    out = []
    for x in range(s, ce, 4):
        ins = fn.dis1(x)
        if ins is None:
            out.append("?")
            continue
        w = fn.rd32(x)
        kind = fn._branch_kind(w, x, s, e)
        if kind in ("CALL", "EXT"):
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            out.append("%s %X" % ("bl" if ins.mnemonic == "blx" else ins.mnemonic, x + 8 + (imm << 2)))
            continue
        if kind == "LOCAL":
            out.append(ins.mnemonic + " LOCAL")
            continue
        lit = None
        lm = fn._LIT.search(ins.op_str)
        if lm:
            la = (x + 8 + fn._pcoff(lm)) & ~3
            v = fn.rd32(la) if fn.in_text(la) else None
            lit = ("?" if v is None else "%X" % v if fn.in_ro(v) or fn.in_text(v)
                   else "ADDR" if fn._looks_addr(v) else "%#x" % v)
        out.append(fn._insn_token(ins, None, lit)[0])
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--k", type=int, default=8, help="window length in instructions")
    ap.add_argument("--min-words", type=int, default=80, help="a 'large' function has more words than this")
    ap.add_argument("--min-users", type=int, default=12, help="unmatched large functions a window must reach")
    ap.add_argument("--top", type=int, default=25)
    a = ap.parse_args()

    status = json.load(open(os.path.join(ROOT, "functions.json")))
    matched = {int(k, 16) for k, v in status.items() if v.get("status") in ("honest", "hack")}
    skip = {int(k, 16) for k, v in status.items() if v.get("status") in SKIP}
    starts = json.load(open(os.path.join(ROOT, "funcs.json")))["starts"]

    toks, words = {}, {}
    for s in sorted(set(starts)):
        if s in skip:
            continue
        try:
            toks[s] = tokens(s)
        except Exception:  # noqa: BLE001 - a start the disassembler cannot walk is not an idiom source
            continue
        words[s] = len(toks[s])

    big = collections.Counter()      # window -> unmatched large functions containing it
    hits = collections.Counter()     # window -> matched functions containing it
    users = collections.defaultdict(set)
    for s, t in toks.items():
        grams = {tuple(t[i:i + a.k]) for i in range(len(t) - a.k + 1)}
        for g in grams:
            if s in matched:
                hits[g] += 1
            elif words[s] > a.min_words:
                big[g] += 1
                users[g].add(s)

    cands = sorted((g for g, n in big.items() if n >= a.min_users and hits[g] <= max(1, n // 10)),
                   key=lambda g: -big[g])
    clusters = []
    for g in cands:
        fs = users[g]
        for c in clusters:
            if len(fs & c["users"]) > 0.5 * len(fs | c["users"]):
                c["grams"].append(g)
                c["all"] |= fs
                break
        else:
            clusters.append(dict(grams=[g], users=fs, all=set(fs)))

    out = ["# Inline idioms of unmatched large functions (k=%d, > %d words)" % (a.k, a.min_words), "",
           "Windows that unmatched large functions share and matched functions (almost) never contain. "
           "Prove the form on the smallest user, put it in a shared header, then reopen its users.", ""]
    for i, c in enumerate(clusters[:a.top]):
        names = sorted({m for g in c["grams"] for t in g for m in ADDR_TOK.findall(t)})
        small = sorted(c["all"] | {s for s, t in toks.items() if s not in matched and words[s] <= a.min_words
                                   and any(_contains(t, g) for g in c["grams"][:1])},
                       key=lambda s: words[s])[:6]
        out.append("## %d. %d unmatched large functions, %d matched" % (
            i + 1, len(c["all"]), max(hits[g] for g in c["grams"])))
        out.append("")
        out.append("`" + " ; ".join(c["grams"][0]) + "`")
        out.append("")
        for m in names:
            out.append("- %s %s" % (m, (fn.name_of(int(m, 16)) or "")[:100]))
        out.append("- smallest users: " + ", ".join("%08X (%d words)" % (s, words[s]) for s in small))
        out.append("")
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    open(OUT, "w", encoding="utf-8").write("\n".join(out) + "\n")
    print("%d clusters from %d windows -> %s" % (len(clusters), len(cands), os.path.relpath(OUT, ROOT)))
    for c in clusters[:a.top]:
        print("%5d  %s" % (len(c["all"]), " ; ".join(c["grams"][0])[:150]))


def _contains(t, g):
    n = len(g)
    return any(tuple(t[i:i + n]) == g for i in range(len(t) - n + 1))


if __name__ == "__main__":
    main()
