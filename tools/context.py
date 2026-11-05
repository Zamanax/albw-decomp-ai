"""Precomputed per-target context for a matching agent.

  python tools/context.py 0xADDR [--start PATH]

Writes logs/manual/<ADDR>/CONTEXT.md (target disassembly, what it references, how the starting
source's externs line up with those references, and matched sources that already name the same
externs) and prints its repo-relative path.
"""
import argparse, bisect, json, os, re, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn

ROOT = fn.ROOT
# extern tokens as matched sources (func_/data_/g_/ro_/bss_) and Ghidra output (FUN_/DAT_/PTR_) name them
TOKEN = re.compile(r"(?:func|data|g|ro|bss|FUN|DAT|PTR)_([0-9A-Fa-f]{8})(?![0-9A-Za-z])")
MAX_RELATED = 5
MAX_LINES = 8

_related = None  # (addr -> [paths], path -> text length)
_branches = None  # target -> [branch source pcs]


def _rel(p):
    return os.path.relpath(p, ROOT).replace("\\", "/")


def related_index():
    """Inverted index over every honest functions.json source: address -> source paths naming it."""
    global _related
    if _related is None:
        funcs = json.load(open(os.path.join(ROOT, "functions.json"), encoding="utf-8"))
        idx, size = {}, {}
        for path in sorted({v["path"] for v in funcs.values() if v.get("status") == "honest" and v.get("path")}):
            try:
                with open(os.path.join(ROOT, path), encoding="utf-8", errors="replace") as f:
                    text = f.read()
            except OSError:
                continue
            size[path] = len(text)
            for a in {int(m, 16) for m in TOKEN.findall(text)}:
                idx.setdefault(a, []).append(path)
        _related = (idx, size)
    return _related


def _branch_index():
    global _branches
    if _branches is None:
        out = {}
        words = struct.unpack_from(f"<{fn.TS // 4}I", fn.CODE, 0)
        for i, w in enumerate(words):
            if (w & 0x0E000000) == 0x0A000000 and (w >> 28) != 0xF:
                imm = w & 0xFFFFFF
                imm = imm - 0x1000000 if imm & 0x800000 else imm
                pc = fn.TA + i * 4
                out.setdefault(pc + 8 + (imm << 2), []).append(pc)
        _branches = out
    return _branches


def _owner(pc):
    s, _ = fn.func_range(pc)
    return fn.name_of(s) or f"func_{s:08X}"


def xrefs(addr):
    """Branches to addr, literal-pool words holding it, and ro/data pointers to it (cmd_xref, indexed)."""
    s, e = fn.func_range(addr)
    hits = []
    for pc in _branch_index().get(addr, []):
        if s <= pc < e:
            continue  # internal loop back to the entry
        kind = "BL" if (fn.rd32(pc) >> 24) & 1 else "B"
        hits.append((kind, pc, f"{kind:7} from {pc:08X} in {_owner(pc)}"))
    pat = struct.pack("<I", addr)
    i = fn.CODE.find(pat)
    while i >= 0:
        if not i & 3:
            a = fn.TA + i
            if fn.in_text(a):
                hits.append(("literal", a, f"literal at {a:08X} in {_owner(a)}"))
            elif fn.in_ro(a) or fn.RA + fn.RS <= a < fn.DA + fn.DS:
                tag = "ro" if fn.in_ro(a) else "data"
                hits.append((tag, a, f"pointer in {tag} at {a:08X}"))
        i = fn.CODE.find(pat, i + 1)
    return hits


def _kind_of_value(v):
    if fn.in_text(v):
        return "func pointer"
    if fn.in_ro(v):
        w = fn.rd32(v) if v + 4 <= fn.RA + fn.RS else 0
        return "vtable" if fn.in_text(w) and w in fn.PTR_T else "global in ro"
    if fn.in_data(v):
        return "global in data"
    return None


def target_refs(s, e, rows):
    """Ordered {addr: kind} for calls/tail branches leaving [s,e) and pool values in text/ro/data."""
    refs = {}
    for a, w, t in rows:
        if t.startswith(".word"):
            continue
        mn, _, ops = t.partition(" ")
        ops = ops.strip()
        if mn.startswith("b") and ops.startswith("#"):
            tgt = int(ops[1:].split()[0], 0)
            if not (s <= tgt < e):
                kind = "call" if (w >> 24) & 1 or (w >> 28) == 0xF else "tail-branch"
                refs.setdefault(tgt, kind)
        m = re.search(r"; =0x([0-9a-f]+)", t)
        if m:
            v = int(m.group(1), 16)
            k = _kind_of_value(v)
            if k:
                refs.setdefault(v, k)
    return refs


def _ref_name(a):
    n = fn.name_of(a)
    if n:
        return n
    return f"data_{a:08X}"


def _defines(text, a):
    """True if the source defines (not just declares) a function named by address a."""
    for line in text.splitlines():
        if line[:1].isspace() or "extern" in line or line.rstrip().endswith(";"):
            continue
        for m in TOKEN.finditer(line):
            if int(m.group(1), 16) == a and line[m.end():].lstrip().startswith("("):
                return True
    return False


def build(addr, start=None, index=None):
    s, e = fn.func_range(addr)
    tag = f"{s:08X}"
    idx, size = index or related_index()
    rows = fn.listing(s, e)
    refs = target_refs(s, e, rows)
    funcs = json.load(open(os.path.join(ROOT, "functions.json"), encoding="utf-8"))
    entry = funcs.get(tag)
    own = entry.get("path") if entry else None

    start_text, start_names = None, set()
    if start:
        sp = start if os.path.isabs(start) else os.path.join(ROOT, start)
        with open(sp, encoding="utf-8", errors="replace") as f:
            start_text = f.read()
        start_names = {int(m, 16) for m in TOKEN.findall(start_text)}
        start = _rel(sp)

    out = []
    how = []
    if s in fn.BL_T:
        how.append("called by BL")
    if s in fn.PTR_T:
        how.append("address stored in ro/data (vtable or callback)")
    hits = xrefs(s)
    if not how:
        how.append("no BL / vtable reference" + (f"; reached by {', '.join(sorted({h[0] for h in hits}))}" if hits else ""))
    out.append(f"# CONTEXT {fn.name_of(s)}")
    out.append("")
    out.append(f"- size: {e - s} bytes ({(e - s) // 4} words), range {s:08X}-{e:08X}")
    out.append(f"- referenced: {', '.join(how)}")
    if entry:
        out.append(f"- functions.json: {entry.get('status')} `{own}` cc {entry.get('cc')} flags `{entry.get('flags')}`")
    if start:
        out.append(f"- start source: `{start}`")
    out.append(f"- callers/refs ({len(hits)} total{', first 10' if len(hits) > 10 else ''}):")
    for _, _, line in hits[:10]:
        out.append(f"  - {line}")
    if not hits:
        out.append("  - none found")
    out.append("")

    out.append("## Disassembly")
    out.append("")
    out.append("```")
    for a, w, t in rows:
        out.append(f"{a:08X}: {w:08X}  {t}")
    out.append("```")
    out.append("")

    out.append("## What the target references")
    out.append("")
    if refs:
        out.append("| address | name | kind | start names it |")
        out.append("|---|---|---|---|")
        for a, k in refs.items():
            named = ("yes" if a in start_names else "no") if start else "-"
            out.append(f"| {a:08X} | {_ref_name(a).replace('|', '/')} | {k} | {named} |")
    else:
        out.append("No calls, tail branches or pool addresses: the function is self-contained.")
    out.append("")

    if start:
        out.append("## Start source vs target")
        out.append("")
        extra = sorted(start_names - set(refs))
        matched = [a for a in refs if a in start_names]
        missing = [a for a in refs if a not in start_names]
        out.append(f"- target references named by start: {len(matched)}; not named: {len(missing)}"
                   + (f" ({', '.join(f'{a:08X}' for a in missing)})" if missing else ""))
        if extra:
            out.append("- start names addresses the target never references (likely twin-specific: replace or drop):")
            for a in extra:
                note = " - defined in the start source: the twin itself, rename to the target" if _defines(start_text, a) else ""
                out.append(f"  - {a:08X} {_ref_name(a)}{note}")
        else:
            out.append("- start names no address outside the target's references")
        out.append(f"- start names {len(matched)} of {len(refs)} target references")
        out.append("")

    out.append("## Related matched sources")
    out.append("")
    skip = {own, start}
    score = {}
    for a in refs:
        for p in idx.get(a, ()):
            if p not in skip:
                score.setdefault(p, set()).add(a)
    ranked = sorted(score.items(), key=lambda kv: (-len(kv[1]), size.get(kv[0], 0), kv[0]))[:MAX_RELATED]
    if not ranked:
        out.append("No honest matched source names any of the target's references.")
    for p, shared in ranked:
        out.append(f"### `{p}` - shares {len(shared)}: {', '.join(f'{a:08X}' for a in sorted(shared))}")
        out.append("")
        try:
            with open(os.path.join(ROOT, p), encoding="utf-8", errors="replace") as f:
                lines = f.read().splitlines()
        except OSError:
            continue
        inc = [l.strip() for l in lines if l.lstrip().startswith("#include")]
        hit = []
        for n, l in enumerate(lines, 1):
            if any(int(m, 16) in shared for m in TOKEN.findall(l)):
                hit.append(f"{n:4}: {l.rstrip()[:160]}")
                if len(hit) >= MAX_LINES:
                    break
        out.append("```")
        if inc:
            out.append("  " + "  ".join(inc)[:200])
        out.extend(hit)
        out.append("```")
        out.append("")

    d = os.path.join(ROOT, "logs", "manual", tag)
    os.makedirs(d, exist_ok=True)
    path = os.path.join(d, "CONTEXT.md")
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(out).rstrip() + "\n")
    return _rel(path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr")
    ap.add_argument("--start", help="repo-relative path of the agent's starting source")
    a = ap.parse_args()
    print(build(int(a.addr, 16), a.start))


if __name__ == "__main__":
    main()
