"""ALBW matching-decomp helper.

  python tools/fn.py show  <addr>                 annotated disassembly of the target function
  python tools/fn.py xref  <addr>                 who calls / references an address
  python tools/fn.py check <file.cpp> <addr> [--sym SUBSTR] [--cc 4.1/b894] [--flags "..."]
                                                   compile with ARMCC and compare against the original
  python tools/fn.py checks <addr> <file> [<file> ...] [--cc CC] [--flags "..."] [--jobs 8]
                                                   check every file in parallel; ranked table, then the full
                                                   check output of the best file
  python tools/fn.py flags <file> <addr> [--cc CC] [--base "..."] [--jobs 8]
                                                   check one file under every refine.flag_variants(base) flag set;
                                                   ranked table, full output of the best, then BEST FLAGS: <flags>

checks/flags rank MATCH first, then fewest OP, then fewest REG+MOVED, then highest word %; a file that does not
compile is ranked last with its first compiler error. Each check appends to check_log.jsonl exactly like `check`.

check prints, after RESULT/IDENTITY, a register-blind alignment of the two instruction streams:
  STRUCTURE: OP=a REG=b MOVED=c aligned n/m  pool p/q
  OP     instructions on one side only, or aligned but different with registers ignored
  REG    aligned, same instruction, different registers
  MOVED  same instruction (registers ignored) on both sides, at different positions
Literal-pool and jump-table words are scored the same way, by value (a relocated word counts as the
address it points at); `pool p/q` is the matched/maximum count of those.
"""
import bisect, difflib, json, os, re, struct, subprocess, sys, time

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_code_path = os.path.join(ROOT, "code.bin")
if not os.path.isfile(_code_path):
    sys.stderr.write(
        "fn.py: code.bin not found at %s\n"
        "Supply the USA dump (6,455,296 bytes, SHA-1 e6ab7d66ee62e879248b0660aaf38d22202e604b)\n"
        "in the repository root; see README.md 'Requirements'.\n" % _code_path)
    raise SystemExit(2)
CODE = open(_code_path, "rb").read()
TA, TS = 0x100000, 5841180
RA, RS = 0x693000, 439800
DA, DS = 0x6FF000, 166384
TEXT_END = TA + TS
DEFAULT_CC = "4.1/b1049"  # b894 inserts NOPs between back-to-back branches; b791..b1454 (except b894) match
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)


def rd32(a):
    return struct.unpack_from("<I", CODE, a - TA)[0]


def in_text(a):
    return TA <= a < TEXT_END


def in_ro(a):
    return RA <= a < RA + RS


def in_data(a):
    return DA <= a < DA + DS + 0x200000  # data + generous bss


_cache = os.path.join(ROOT, "funcs.json")


def build_table():
    words = struct.unpack_from(f"<{TS // 4}I", CODE, 0)
    bl, ptr, pro = set(), set(), set()
    for i, w in enumerate(words):
        if (w & 0x0F000000) == 0x0B000000 and (w >> 28) != 0xF:
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            t = TA + i * 4 + 8 + (imm << 2)
            if in_text(t):
                bl.add(t)
        if (w & 0xFFFF4000) == 0xE92D4000 or w == 0xE52DE004:
            pro.add(TA + i * 4)
    for lo, sz in ((RA, RS), (DA, DS)):
        n = sz // 4
        for w in struct.unpack_from(f"<{n}I", CODE, lo - TA):
            if in_text(w) and not w & 3:
                ptr.add(w)

    def is_end(w):
        return (w == 0xE12FFF1E or (w & 0xFFFF8000) == 0xE8BD8000 or w == 0xE49DF004
                or (w & 0xFF000000) == 0xEA000000 or w == 0 or (w & 0xFFFFFFF0) == 0xE12FFF10)

    # literal-pool words: targets of PC-relative LDR / VLDR
    pool = set()
    for i, w in enumerate(words):
        if (w & 0x0F7F0000) == 0x051F0000 or (w & 0x0F3F0E00) == 0x0D1F0A00:
            off = (w & 0xFFF) if (w & 0x0F000000) == 0x05000000 else (w & 0xFF) * 4
            pool.add(TA + i * 4 + 8 + (off if w & 0x00800000 else -off))
        elif (w & 0x0FEF0000) in (0x028F0000, 0x024F0000):  # ADR: inline string/data, mark until its NUL
            rot = ((w >> 8) & 0xF) * 2
            v = ((w & 0xFF) >> rot | (w & 0xFF) << (32 - rot)) & 0xFFFFFFFF if rot else w & 0xFF
            t = TA + i * 4 + 8 + (v if (w & 0x0FEF0000) == 0x028F0000 else -v)
            t &= ~3
            for _ in range(64):
                if not in_text(t):
                    break
                pool.add(t)
                if 0 in struct.pack("<I", rd32(t)):
                    break
                t += 4

    def stops(i):
        """True if the word at index i ends a function: unconditional return/branch, pool data or padding."""
        w = words[i]
        return (is_end(w) or (w & 0xFFFFF000) == 0xE59FF000 or w == 0xE1A00000
                or (TA + i * 4) in pool)

    # pointer targets count when preceded by a return/branch or by literal-pool data
    ptr_ok = {a for a in ptr if a == TA or stops((a - TA) // 4 - 1)}
    starts = sorted(pro | bl | ptr_ok)
    # tail-call-only functions (leaf functions reached by a plain "b" from another function):
    # the target follows a stop and the branch comes from a different function
    tail = set()
    for i, w in enumerate(words):
        if (w & 0x0F000000) == 0x0A000000 and (w >> 28) != 0xF:
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            src = TA + i * 4
            t = src + 8 + (imm << 2)
            if (in_text(t) and t > TA and t not in pool and stops((t - TA) // 4 - 1)
                    and bisect.bisect_right(starts, src) != bisect.bisect_right(starts, t)):
                # a real entry never reads the caller's frame before its own push / sub sp
                j = (t - TA) // 4
                frame = False
                for k in range(j, min(j + 6, len(words))):
                    x = words[k]
                    if (x & 0xFFFF0000) in (0xE92D0000, 0xE24DD000) or x == 0xE52DE004 or (x & 0xFFBF0F00) == 0xED2D0B00:
                        break
                    if (x & 0x0C0F0000) == 0x040D0000 and (x & 0xFFF) and (x >> 28) != 0xF:
                        frame = True  # ldr/str [sp, #imm] before any frame setup
                        break
                if not frame:
                    tail.add(t)
    starts = sorted(a for a in set(starts) | tail if a not in pool)  # a literal-pool word is never a function start
    # starts nothing references (e.g. a setter reached only through a linker-NOPped forwarder), added by hand
    xf = os.path.join(ROOT, "shared", "extra_starts.txt")
    extra = set()
    if os.path.exists(xf):
        extra = {int(l.split()[0], 16) for l in open(xf) if l.strip() and not l.startswith("#")}
        starts = sorted(set(starts) | {a for a in extra if in_text(a)})
    fixed = set()
    for k, a in enumerate(starts):
        i = (a - TA) // 4
        if k == 0 or stops(i - 1) or a in extra:  # hand-verified starts stay (e.g. after a 0xFFFFFFFF pool word)
            fixed.add(a)
            continue
        # ARMCC may schedule up to 3 unconditional instructions before the push:
        # the real start follows the previous stop
        for back in (1, 2, 3):
            if i - back - 1 < 0 or (words[i - back] >> 28) != 0xE:
                break  # conditional code before the push: shrink-wrapped, same function
            if stops(i - back - 1):
                fixed.add(a - 4 * back)
                break
        # otherwise the previous code falls through into it (e.g. a shrink-wrapped push): same function
    starts = sorted(fixed)
    # false starts (an internal basic block that our heuristics took for a function), removed by hand
    nf = os.path.join(ROOT, "shared", "not_starts.txt")
    if os.path.exists(nf):
        drop = {int(l.split()[0], 16) for l in open(nf) if l.strip() and not l.startswith("#")}
        starts = sorted(set(starts) - drop)
    json.dump({"starts": starts, "bl": sorted(bl), "ptr": sorted(ptr)}, open(_cache, "w"))


if not os.path.exists(_cache):
    build_table()
_t = json.load(open(_cache))
STARTS = _t["starts"]
BL_T = set(_t["bl"])
PTR_T = set(_t["ptr"])


def func_range(addr):
    i = bisect.bisect_right(STARTS, addr) - 1
    s = STARTS[i]
    e = STARTS[i + 1] if i + 1 < len(STARTS) else TEXT_END
    return s, e


def cstring(a):
    off = a - TA
    end = CODE.find(b"\0", off, off + 200)
    if end <= off:
        return None
    s = CODE[off:end]
    try:
        t = s.decode("utf-8")
    except UnicodeDecodeError:
        return None
    if len(t) >= 2 and all(c.isprintable() for c in t):
        return t
    return None


SYMS_FILE = os.path.join(ROOT, "shared", "symbols.jsonl")


def known_symbols():
    """Names/signatures agents have registered with `kb.py sym` (latest entry per address wins)."""
    out = {}
    if os.path.exists(SYMS_FILE):
        for line in open(SYMS_FILE, encoding="utf-8"):
            try:
                d = json.loads(line)
                out[int(d["addr"], 16)] = d
            except (ValueError, KeyError):
                pass
    return out


_SYMS = known_symbols()


def name_of(a):
    if in_text(a):
        s, _ = func_range(a)
        base = f"func_{a:08X}" if s == a else f"func_{s:08X}+{a - s:#x}"
        k = _SYMS.get(a)
        return f"{base} <{k['name']}>" if k else base
    if a in _SYMS:
        return f"{a:08X} <{_SYMS[a]['name']}>"
    if in_ro(a):
        st = cstring(a)
        return f'ro_{a:08X} "{st}"' if st else f"ro_{a:08X}"
    if in_data(a):
        return f"data_{a:08X}" if a < DA + DS else f"bss_{a:08X}"
    return None


def dis1(a):
    """Decode the single ARM word at a (None if it is not a valid instruction)."""
    l = list(md.disasm(CODE[a - TA:a - TA + 4], a, 1))
    return l[0] if l else None


def code_end(start, end):
    """Split [start,end) into instructions and trailing literal pool (words loaded PC-relative)."""
    pool = set()
    for a in range(start, end, 4):
        ins = dis1(a)
        if ins is None:
            continue
        m = re.search(r"\[pc(?:, #(-?0x[0-9a-f]+|-?\d+))?\]", ins.op_str)
        if m and ins.mnemonic.startswith(("ldr", "vldr")):
            tgt = ins.address + 8 + int(m.group(1), 0) if m.group(1) else ins.address + 8
            if start <= tgt < end:
                pool.add(tgt & ~3)
    ce = end
    while ce - 4 >= start and (ce - 4) in pool:
        ce -= 4
    return ce, pool


_tiny = None


def tiny_getters():
    """Getters 'ldr*  r0, [r0, #imm]; bx lr' that armlink --inline copies into their callers.
    Maps the load word to the getter address (only words unique to one getter)."""
    global _tiny
    if _tiny is None:
        seen = {}
        for a in range(TA + 4, TA + TS - 4, 4):
            w = rd32(a)
            if rd32(a + 4) != 0xE12FFF1E or (w >> 28) != 0xE or (w >> 12) & 0xFF != 0:  # Rn = r0, Rd = r0
                continue
            ld = ((w & 0x0F100000) in (0x05100000, 0x07100000) or  # ldr / ldrb, ldr reg-offset
                  (w & 0x0F1000F0) in (0x011000B0, 0x011000D0, 0x011000F0))  # ldrh / ldrsb / ldrsh
            p = rd32(a - 4)
            if ld and (p in (0xE12FFF1E, 0xE1A00000) or (p & 0xFFFF8000) == 0xE8BD8000 or (p & 0xFF000000) == 0xEA000000):
                seen.setdefault(w, []).append(a)
        _tiny = {w: v[0] for w, v in seen.items() if len(v) == 1}
    return _tiny


def listing(start, end, data_words=None):
    """Return list of (addr, word, text) for [start,end)."""
    ce, pool = code_end(start, end)
    out = []
    for a in range(start, ce, 4):
        ins = dis1(a)
        if ins is None or a in pool:  # data inside the code (jump-table data, inline pool)
            out.append((a, rd32(a), f".word {rd32(a):#010x}"))
            continue
        txt = f"{ins.mnemonic:8} {ins.op_str}"
        note = ""
        if ins.mnemonic.startswith(("bl", "b")) and ins.op_str.startswith("#"):
            t = int(ins.op_str[1:], 0)
            if not (start <= t < end):
                note = name_of(t) or ""
            else:
                note = f"<+{t - start:#x}>"
        m = re.search(r"\[pc(?:, #(-?0x[0-9a-f]+|-?\d+))?\]", ins.op_str)
        if m:
            la = ins.address + 8 + int(m.group(1), 0) if m.group(1) else ins.address + 8
            if in_text(la):
                v = rd32(la & ~3)
                note = f"={v:#x} {name_of(v) or ''}".rstrip()
        if not note and a > start:
            g = tiny_getters().get(rd32(a))
            if g and g != start:
                note = f"maybe linker-inlined call to {name_of(g) or f'func_{g:08X}'} (KB #111)"
        if note:
            txt += f"   ; {note}"
        out.append((ins.address, rd32(ins.address), txt))
    for a in range(ce, end, 4):
        v = rd32(a)
        n = name_of(v)
        out.append((a, v, f".word {v:#010x}" + (f"   ; {n}" if n else "")))
    return out


def cmd_show(addr):
    s, e = func_range(addr)
    refs = []
    if s in BL_T:
        refs.append("called by BL")
    if s in PTR_T:
        refs.append("address stored in ro/data (vtable or callback)")
    print(f"func_{s:08X}  size {e - s:#x} ({e - s} bytes)  [{', '.join(refs) or 'no direct refs found'}]")
    for a, w, t in listing(s, e):
        print(f"  {a:08X}: {w:08X}  {t}")


def cmd_xref(addr):
    hits = []
    words = struct.unpack_from(f"<{TS // 4}I", CODE, 0)
    for i, w in enumerate(words):
        pc = TA + i * 4
        if (w & 0x0E000000) == 0x0A000000 and (w >> 28) != 0xF:
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            if pc + 8 + (imm << 2) == addr:
                hits.append(f"  branch from {pc:08X} in {name_of(pc)}")
        elif w == addr:
            hits.append(f"  literal at {pc:08X} in {name_of(pc)}")
    for lo, sz, tag in ((RA, RS, "ro"), (DA, DS, "data")):
        for j in range(0, sz - 3, 4):
            if rd32(lo + j) == addr:
                hits.append(f"  pointer in {tag} at {lo + j:08X}")
    print("\n".join(hits[:60]) or "  no references")
    if len(hits) > 60:
        print(f"  ... {len(hits) - 60} more")


# ---------------- ELF object parsing ----------------
def parse_elf(path):
    d = open(path, "rb").read()
    shoff, = struct.unpack_from("<I", d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2E)
    secs = []
    for i in range(shnum):
        nm, ty, fl, ad, off, sz, link, info, al, es = struct.unpack_from("<10I", d, shoff + i * shentsize)
        secs.append(dict(name=nm, type=ty, off=off, size=sz, link=link, info=info, es=es))
    shs = secs[shstrndx]

    def sname(o, tab):
        e = d.index(b"\0", tab["off"] + o)
        return d[tab["off"] + o:e].decode("latin1")

    for s in secs:
        s["name"] = sname(s["name"], shs)
    syms = []
    for s in secs:
        if s["type"] == 2:  # SYMTAB
            strt = secs[s["link"]]
            for j in range(s["size"] // 16):
                nm, val, sz, info, oth, shn = struct.unpack_from("<IIIBBH", d, s["off"] + j * 16)
                syms.append(dict(name=sname(nm, strt), value=val, size=sz, type=info & 0xF, shndx=shn))
    rels = {}
    for s in secs:
        if s["type"] == 9:  # REL
            lst = rels.setdefault(s["info"], [])
            for j in range(s["size"] // 8):
                off, info = struct.unpack_from("<II", d, s["off"] + j * 8)
                lst.append((off, info & 0xFF, syms[info >> 8]["name"] if (info >> 8) < len(syms) else "?"))
    return d, secs, syms, rels


# ---------------- relocation identity ----------------
# fn.py check masks relocated words (call targets, pool addresses): a source that calls the wrong function still
# prints MATCH. Extern names that end in an address ("g_104918", "func_00100B88", "FUN_0010A2C4") say which target
# they mean, so for those the target the original word resolves to can be compared with the name.
_ADDR_TAIL = re.compile(r"(?:^|_)(?:0x)?([0-9A-Fa-f]{6,8})$")


def _identifier(name):
    """Identifier of a plain or Itanium-mangled symbol (_ZN3Foo8g_104918Ev -> g_104918); None if not a plain name."""
    if not name.startswith("_Z"):
        return name
    i, ids = 2, []
    nested = name[i:i + 1] == "N"
    if nested:
        i += 1
        while name[i:i + 1] in ("r", "V", "K", "R", "O"):
            i += 1
    if name[i:i + 1] == "L":  # internal linkage
        i += 1
    while name[i:i + 1].isdigit():
        j = i
        while name[j:j + 1].isdigit():
            j += 1
        n = int(name[i:j])
        ids.append(name[j:j + n])
        i = j + n
        if not nested:
            break
    if not ids or (nested and name[i:i + 1] in ("C", "D")):  # constructors/destructors are named by their class
        return None
    return ids[-1]


def named_address(name):
    """The address an extern's name claims (trailing hex in the game image), or None."""
    ident = _identifier(name)
    m = ident and _ADDR_TAIL.search(ident)
    if not m:
        return None
    a = int(m.group(1), 16)
    return a if in_text(a) or in_ro(a) or in_data(a) else None


def address_named(name):
    """Plain identifier of an address-named symbol (g_104918; mangled names by their identifier), else None."""
    ident = _identifier(name)
    return ident if ident and _ADDR_TAIL.search(ident) else None


def reloc_identity(s, rows):
    """Compare each matched relocated word's real target with the address its symbol name claims.
    Returns (verified, unverifiable, [(offset, name, claimed, actual)])."""
    ok, unknown, bad = 0, 0, []
    for i, tw, mw, same, rel in rows:
        if not (rel and same):
            continue
        typ, name = rel
        a = s + i * 4
        imm = ((tw & 0xFFFFFF) ^ 0x800000) - 0x800000
        if typ in (1, 28, 29) and (tw & 0x0E000000) == 0x0A000000:
            got = a + 8 + imm * 4  # b / bl
        elif typ in (1, 28) and (tw >> 25) == 0x7D:
            got = a + 8 + imm * 4 + ((tw >> 23) & 2)  # bl turned into blx by the linker
        elif typ == 29 and tw == 0xE1A00000:
            got = a + 4  # tail call to the very next function, turned into a NOP by the linker
        elif typ == 2:
            got = (tw - mw) & 0xFFFFFFFF  # absolute pool word minus the in-place addend
        else:
            got = None  # call inlined by the linker: target not recoverable
        want = named_address(name)
        if got is None or want is None:
            unknown += 1
        elif got & ~1 == want & ~1:
            ok += 1
        else:
            bad.append((i * 4, name, want, got))
    return ok, unknown, bad


# ---------------- structural score ----------------
# Register names as capstone prints them (r9-r12 come out as sb/sl/fp/ip).
REGTOK = re.compile(r"\b(?:r\d+|sb|sl|fp|ip|sp|lr|pc|[sdq]\d+)\b")
_LIT = re.compile(r"\[pc(?:, #(-?0x[0-9a-f]+|-?\d+))?\]")
def _pcoff(m):
    """The pc-relative offset of a `[pc]`/`[pc, #n]` match (capstone omits a zero offset)."""
    return int(m.group(1), 0) if m.group(1) else 0


_ADR = re.compile(r"^(\w+), pc, #(?:0x[0-9a-f]+|\d+)$")


def _looks_addr(v):
    """A word that points into the game image (text, rodata, data or bss)."""
    return TA <= v < DA + DS + 0x200000


def _insn_token(ins, branch=None, lit=None):
    """(register-blind text, full text) of one instruction. branch: CALL / EXT / LOCAL for b/bl (targets
    are position- and link-dependent); lit: the value its pc-relative load reads (ADDR when relocated)."""
    m, op = ins.mnemonic, ins.op_str
    if branch:
        full = f"{'bl' if m == 'blx' else m} {branch}"
        return full, full
    if lit is not None:
        op = _LIT.sub("=" + lit, op)
    elif m.startswith(("add", "sub")) and _ADR.match(op):
        op = _ADR.match(op).group(1) + ", pc, LOCAL"  # adr: the offset depends on the position
    full = f"{m} {op}"
    return REGTOK.sub("R", full), full


def _branch_kind(w, here, lo, hi):
    """CALL / EXT / LOCAL for an immediate b/bl/blx word at address here (function spans [lo, hi)), else None."""
    if (w >> 25) == 0x7D:
        return "CALL"
    if (w & 0x0E000000) != 0x0A000000 or (w >> 28) == 0xF:
        return None
    if w & 0x01000000:
        return "CALL"
    imm = w & 0xFFFFFF
    imm = imm - 0x1000000 if imm & 0x800000 else imm
    return "LOCAL" if lo <= here + 8 + (imm << 2) < hi else "EXT"


def _tiny_callee(a):
    """A function armlink may inline to nothing: a leaf of at most four instructions, ending in `bx lr`,
    `pop {..., pc}` or `mov pc, lr`."""
    for k in range(4):
        if not in_text(a + 4 * k):
            return False
        w = rd32(a + 4 * k)
        if (w & 0x0FFFFFFF) in (0x012FFF1E, 0x01A0F00E) or (w & 0x0FFF8000) == 0x08BD8000:
            return True
        if (w & 0x0E000000) == 0x0A000000:
            return False  # a branch: not a leaf
    return False


def _align(T, M):
    """diff two token lists. Returns (equal block ranges, unpaired token lists per changed block)."""
    sm = difflib.SequenceMatcher(None, T, M, autojunk=False)
    equal, blocks = [], []
    for tag, a1, a2, b1, b2 in sm.get_opcodes():
        if tag == "equal":
            equal.append((a1, b1, a2 - a1))
        else:
            blocks.append((T[a1:a2], M[b1:b2]))
    from collections import Counter
    pairs = Counter(x for bt, _ in blocks for x in bt) & Counter(x for _, bm in blocks for x in bm)
    left_t, left_m = Counter(pairs), Counter(pairs)

    def unpaired(seq, left):
        out = []
        for x in seq:
            if left[x] > 0:
                left[x] -= 1
            else:
                out.append(x)
        return out

    return equal, [(unpaired(bt, left_t), unpaired(bm, left_m)) for bt, bm in blocks], sum(pairs.values())


def structure(s, e, ce, tpool, jt, mine, fsize, relmap, rows):
    """Register-blind alignment of the original [s,e) and our bytes.
    Returns dict(op, reg, moved, aligned, total, pool, ops); ops lists the OP instructions (register-blind),
    "-" = only in the original, "+" = only in ours; pool is (matched, original, ours) pool words.

    Each instruction becomes (register-blind text, full text); literal-pool and jump-table words are scored
    separately, by value. Rows the positional compare
    already accepted (linker fix-ups: calls, BLX, inlined tiny callees, NOP'd tail calls) take the original's
    token, so every masking rule of the word compare carries over. The streams are aligned on the register-blind
    text: aligned pairs whose full text differs are REG; unaligned leftovers that pair up across the two sides
    (same register-blind text) are MOVED; the rest are OP, counted per changed block as max(original side, our
    side) so one substituted instruction is one OP. Each pool word is compared with the pool word at the same
    place (dropped when the word compare masks it), so code that is right but whose pool holds another constant
    does not read as a match."""
    n_t, n_m = (e - s) // 4, len(mine) // 4
    mw = struct.unpack_from(f"<{n_m}I", mine, 0)

    tt = [None] * n_t
    for i in range(n_t):
        a = s + i * 4
        if a >= ce or a in tpool or a in jt:
            continue
        ins = dis1(a)
        if ins is None:
            continue
        w = rd32(a)
        lit = None
        lm = _LIT.search(ins.op_str)
        if lm:
            la = (a + 8 + _pcoff(lm)) & ~3
            v = rd32(la) if in_text(la) else None
            lit = "?" if v is None else "ADDR" if _looks_addr(v) else f"{v:#x}"
            if v is not None and ins.op_str.startswith("d") and in_text(la + 4):
                lit += f":{rd32(la + 4):#x}"
        tt[i] = _insn_token(ins, _branch_kind(w, a, s, e), lit)

    # our side: pool = the words a pc-relative load reads, and ABS32 (data pointer) words
    decoded = [next(md.disasm(struct.pack("<I", w), i * 4, 1), None) for i, w in enumerate(mw)]
    mpool = set()
    for i, ins in enumerate(decoded):
        lm = ins and _LIT.search(ins.op_str)
        if lm and ins.mnemonic.startswith(("ldr", "vldr")):
            mpool.add((i * 4 + 8 + _pcoff(lm)) // 4)
    mt = [None] * n_m
    for i, ins in enumerate(decoded):
        rel = relmap.get(i * 4)
        if ins is None or i * 4 >= fsize or i in mpool or (rel and rel[0] == 2):
            continue
        w = mw[i]
        branch = _branch_kind(w, i * 4, 0, fsize)
        if branch and rel:  # relocated: the target is outside this function
            branch = "CALL" if branch == "CALL" else "EXT"
        lit = None
        lm = _LIT.search(ins.op_str)
        if lm:
            li = (i * 4 + 8 + _pcoff(lm)) // 4
            if 0 <= li < n_m:
                lrel = relmap.get(li * 4)
                v = mw[li]
                lit = "ADDR" if (lrel and lrel[0] == 2) or _looks_addr(v) else f"{v:#x}"
                if ins.op_str.startswith("d") and li + 1 < n_m:
                    lit += f":{mw[li + 1]:#x}"
            else:
                lit = "?"
        mt[i] = _insn_token(ins, branch, lit)

    for i, tw, _mw, ok, rel in rows:  # positional fix-ups the word compare accepted
        if not (ok and i < n_t and i < n_m and tt[i] and mt[i]):
            continue
        # "call to a tiny function inlined by the linker" masks a call of ours behind a non-branch word of
        # the original. Behind an ARM NOP the original's callee was inlined to nothing: armlink does that to
        # a leaf of a few instructions (`bx lr` / `pop {.., pc}`). A call of ours to an image function that is
        # not a leaf is a real difference (a wrong callee); a callee outside the image cannot be checked here.
        if (tw == 0xE1A00000 and rel and rel[0] in (1, 28) and
                ((_mw >> 25) == 0x7D or (_mw & 0x0E000000) == 0x0A000000)):
            ca = named_address(rel[1])
            if ca and in_text(ca) and not _tiny_callee(ca):
                continue  # a call to a real function where the original has none: OP
        mt[i] = tt[i]

    T = [x for x in tt if x]
    M = [x for x in mt if x]
    equal, blocks, moved = _align([x[0] for x in T], [x[0] for x in M])
    aligned = sum(n for _, _, n in equal)
    reg = sum(T[a1 + k][1] != M[b1 + k][1] for a1, b1, n in equal for k in range(n))

    op, ops = 0, []
    for ut, um in blocks:
        op += max(len(ut), len(um))
        ops += ["-" + x for x in ut] + ["+" + x for x in um]

    # literal pool / jump-table data, by value: pointers are unverifiable until link time (masked on both
    # sides), and a relocated word of ours holds no value yet, so that position cannot be compared at all.
    masked = {i for i, tw, _m, ok, _ in rows if ok and tw != _m}  # a difference the word compare masks
    ptok = ["ADDR" if _looks_addr(rd32(s + i * 4)) else f"{rd32(s + i * 4):#x}"
            for i in range(n_t) if (s + i * 4 in tpool or s + i * 4 in jt) and i not in masked]
    pok = []
    for i in range(n_m):
        rel = relmap.get(i * 4)
        if i not in masked and (i in mpool or (rel and rel[0] == 2)):
            if rel and rel[0] == 2 and not _looks_addr(mw[i]):
                pok.append("?")
            else:
                pok.append("ADDR" if _looks_addr(mw[i]) else f"{mw[i]:#x}")
    pmatch = 0
    for k in range(max(len(ptok), len(pok))):
        t = ptok[k] if k < len(ptok) else None
        o = pok[k] if k < len(pok) else None
        if o == "?":
            continue  # ours is a relocated word: its value is only known after linking
        if t is not None and t == o:
            pmatch += 1
            continue
        op += 1
        ops += (["-" + t] if t is not None else []) + (["+" + o] if o is not None and o != "?" else [])
    return dict(op=op, reg=reg, moved=moved, aligned=aligned, total=max(len(T), len(M)), ops=ops,
                pool=(pmatch, len(ptok), len(pok)))


def cmd_check(src, addr, sym=None, cc=DEFAULT_CC, flags=DEFAULT_FLAGS, prebuilt=False):
    s, e = func_range(addr)
    if prebuilt:  # the caller already compiled src to obj (e.g. many files in one armcc call)
        obj = os.path.splitext(src)[0] + ".o"
        if not os.path.exists(obj):
            print("COMPILE ERROR\n(no object)")
            return
    else:
        # per-process object: parallel checks of functions sharing one source file must not clobber each other
        obj = "%s.%d.o" % (os.path.splitext(src)[0], os.getpid())
        exe = os.path.join(ROOT, "tools", "armcc", *cc.split("/"), "bin", "armcc.exe")
        # 4.1/b1049 ships a broken Authenticode signature that Windows re-verifies on every launch (serialized, ~4/s);
        # b1049ns is the same exe with the certificate table stripped (code untouched, identical output, verified).
        fast = os.path.join(ROOT, "tools", "armcc", "4.1", "b1049ns", "bin", "armcc.exe")
        if cc == "4.1/b1049" and os.name == "nt" and os.path.exists(fast):
            exe = fast
        if not os.path.exists(exe):
            print("COMPILE ERROR\narmcc not found at %s\n"
                  "Place ARM Compiler 4.1 (build 1049) under tools/armcc/; see README.md 'Requirements'." % exe)
            return
        lang = "--cpp" if src.endswith((".cpp", ".cc")) else "--c99"
        inc = os.path.join(ROOT, "shared", "include")
        args = [exe, "-c", lang] + flags.split() + ["-I", inc, "-o", obj, src]
        if os.name != "nt":
            args = ["wine"] + args  # Linux server: the Windows compiler runs under Wine
        r = subprocess.run(args, capture_output=True, text=True)
        msg = (r.stdout + r.stderr).strip()
        if r.returncode != 0:
            print("COMPILE ERROR\n" + msg)
            return
        if msg:
            print(msg)
    try:
        d, secs, syms, rels = parse_elf(obj)
    finally:
        if not prebuilt and os.path.exists(obj):
            os.remove(obj)
    funcs = [x for x in syms if x["type"] == 2 and x["shndx"] not in (0, 0xFFF1) and x["size"] and "$$" not in x["name"]]
    if sym:
        funcs = [x for x in funcs if sym in x["name"]]
    if not funcs:
        print("no matching function symbol in object; symbols:", [x["name"] for x in syms if x["type"] == 2])
        return
    e_full = e
    while e - 4 > s and rd32(e - 4) == 0xE1A00000:  # alignment padding before the next function
        e -= 4
    if e < e_full and code_end(s, e)[0] >= e:
        lw = rd32(e - 4)
        if not ((lw & 0x0FFFFFFF) == 0x012FFF1E or (lw & 0x0FFF8000) == 0x08BD8000
                or (lw & 0x0F000000) == 0x0A000000 or (lw & 0x0FFFF000) == 0x059FF000) or (lw >> 28) != 0xE:
            e += 4  # the linker turned a final tail call "b next_function" into a NOP: it belongs to us
    target = CODE[s - TA:e - TA]

    def compare(f):
        sec = secs[f["shndx"]]
        # the symbol size excludes the literal pool; extend to the next function (or section end)
        fend = min([x["value"] for x in syms if x["shndx"] == f["shndx"] and x["type"] == 2 and x["value"] > f["value"]
                    and "$$" not in x["name"]] + [sec["size"]])
        mine = d[sec["off"] + f["value"]: sec["off"] + fend]
        relmap = {o - f["value"]: (t, n) for o, t, n in rels.get(f["shndx"], []) if f["value"] <= o < fend}
        n_t, n_m = len(target) // 4, len(mine) // 4
        same = 0
        rows = []
        for i in range(max(n_t, n_m)):
            tw = struct.unpack_from("<I", target, i * 4)[0] if i < n_t else None
            mw = struct.unpack_from("<I", mine, i * 4)[0] if i < n_m else None
            ok = tw == mw
            if not ok and tw is not None and mw is not None:
                rel = relmap.get(i * 4)
                if rel and rel[0] in (1, 28, 29) and (tw & 0xFF000000) == (mw & 0xFF000000):
                    ok = True  # call / jump target fixed up by the linker
                elif rel and rel[0] in (1, 28) and (tw >> 25) == 0x7D:
                    ok = True  # BL turned into BLX by the linker (callee is Thumb)
                elif rel and rel[0] == 2:
                    ok = True  # absolute address in literal pool
                elif rel and rel[0] in (1, 28) and (tw & 0x0E000000) != 0x0A000000:
                    ok = True  # call to a tiny function inlined by the linker (e.g. "mov r0, r0")
                elif rel and rel[0] == 29 and tw == 0xE1A00000:
                    ok = True  # tail call to the very next function, turned into a NOP by the linker
                elif (rel and rel[0] == 29 and (mw & 0x0F000000) == 0x0B000000 and (tw >> 28) == (mw >> 28)
                      and (tw & 0x0E000000) != 0x0A000000):
                    ok = True  # conditional call (blne) to a one-instruction function, inlined by the linker
                elif (tw & 0x0E000000) == 0x0A000000 and (tw & 0xFF000000) == (mw & 0xFF000000):
                    imm = tw & 0xFFFFFF
                    imm = imm - 0x1000000 if imm & 0x800000 else imm
                    if not (s <= s + i * 4 + 8 + (imm << 2) < e):
                        ok = True  # branch out of the function, resolved at link time
            same += ok
            rows.append((i, tw, mw, ok, relmap.get(i * 4)))
        return same, n_t, n_m, rows, mine, relmap

    # with several functions in the file, compare against the one that matches best
    results = [(compare(f), f) for f in funcs]
    results.sort(key=lambda r: (r[0][0] == max(r[0][1], r[0][2]) and r[0][1] == r[0][2],
                                r[0][0] / max(r[0][1], r[0][2], 1)), reverse=True)
    (same, n_t, n_m, rows, mine, relmap), f = results[0]
    if len(funcs) > 1:
        print(f"{len(funcs)} functions in object, best match is {f['name']} (use --sym to force another)")

    total = max(n_t, n_m)
    pct = 100.0 * same / total if total else 0
    exact = same == total and n_t == n_m

    # alignment-based similarity: insertions/deletions don't wreck everything after them
    ce, tpool = code_end(s, e)
    # switch jump tables after "ldr pc, [pc, rX, lsl #2]" hold absolute addresses (ABS32 in our object)
    jt = set()
    for a in range(s, e, 4):
        if (rd32(a) & 0x0FFFFFF0) == 0x079FF100:
            j = a + 8
            while j < e and s <= rd32(j) < e:
                jt.add(j)
                j += 4

    def tok_t(i):
        a = s + i * 4
        w = rd32(a)
        if a >= ce or a in tpool or a in jt:
            return ("P",)
        if (w >> 25) == 0x7D:
            return ("BR", 0xEB)  # BLX made by the linker counts as BL
        if (w & 0x0E000000) == 0x0A000000:
            return ("BR", w >> 24)
        return w

    def tok_m(i):
        w = struct.unpack_from("<I", mine, i * 4)[0]
        rel = relmap.get(i * 4)
        if rel and rel[0] == 2:
            return ("P",)
        if (w & 0x0E000000) == 0x0A000000:
            return ("BR", w >> 24)
        return w

    tt = [tok_t(i) for i in range(n_t)]
    mt = [tok_m(i) for i in range(n_m)]
    sm = difflib.SequenceMatcher(None, tt, mt, autojunk=False)
    sim = 100.0 if exact else 100.0 * sm.ratio()
    print(f"target func_{s:08X} {len(target)} bytes | yours '{f['name']}' {len(mine)} bytes")
    print(f"RESULT: {'MATCH' if exact else 'NO MATCH'}  {same}/{total} words ({pct:.1f}%)  similarity {sim:.1f}%")
    if exact:
        n_ok, n_unk, bad = reloc_identity(s, rows)
        print(f"IDENTITY: {n_ok} verified, {n_unk} unverifiable, {len(bad)} MISMATCH")
        for off, name, want, got in bad:
            print(f"  !! +{off:#x} '{name}' names {want:#010x}, the original targets {got:#010x}")
    else:  # words are not aligned with the original: relocated words would be compared with unrelated ones
        print("IDENTITY: not checked (no match)")
    st = structure(s, e, ce, tpool, jt, mine, f["size"], relmap, rows)
    print(f"STRUCTURE: OP={st['op']} REG={st['reg']} MOVED={st['moved']} aligned {st['aligned']}/{st['total']}"
          f"  pool {st['pool'][0]}/{max(st['pool'][1], st['pool'][2])}")
    if st["ops"]:
        print("STRUCTURE OPS: " + " | ".join(st["ops"][:12]) + (" | ..." if len(st["ops"]) > 12 else ""))

    def dis(w, a):
        if w is None:
            return ""
        l = list(md.disasm(struct.pack("<I", w), a))
        return f"{l[0].mnemonic} {l[0].op_str}" if l else f".word {w:#x}"

    if not exact and n_t == n_m:
        print(f"  {'off':>5}  {'original':38} {'yours':38}")
        for i, tw, mw, ok, rel in rows:
            mark = "  " if ok else "!!"
            r = f" [{rel[1]}]" if rel else ""
            print(f"{mark}{i * 4:5x}  {dis(tw, s + i * 4):38} {dis(mw, s + i * 4):38}{r}")
    elif not exact:
        print("sizes differ: aligned diff (only changed blocks, 2 lines of context)")
        print(f"  {'orig':>5} {'mine':>5}  {'original':38} {'yours':38}")
        for group in sm.get_grouped_opcodes(2):
            print("  ---")
            for op, a1, a2, b1, b2 in group:
                for k in range(max(a2 - a1, b2 - b1)):
                    ti, mi = a1 + k, b1 + k
                    tw = rd32(s + ti * 4) if ti < a2 else None
                    mw = struct.unpack_from("<I", mine, mi * 4)[0] if mi < b2 else None
                    mark = "  " if op == "equal" else "!!"
                    print(f"{mark}{ti * 4 if tw is not None else '':>5} {mi * 4 if mw is not None else '':>5}  "
                          f"{dis(tw, s + ti * 4):38} {dis(mw, s + mi * 4):38}")
    log = os.path.join(os.path.dirname(os.path.abspath(src)), "check_log.jsonl")
    with open(log, "a") as fh:
        # "end" = the range end used; a check run with an in-memory patched table logs a range that differs
        # from funcs.json, so tools can reject it (make_done.py / auto_harvest.py re-verify against the real table)
        fh.write(json.dumps({"t": time.strftime("%H:%M:%S"), "addr": f"{s:08X}", "end": f"{e_full:08X}",
                             "src": os.path.basename(src), "pct": round(pct, 1), "sim": round(sim, 1), "match": exact,
                             "op": st["op"], "reg": st["reg"], "moved": st["moved"],
                             "pool": list(st["pool"]), "cc": cc, "flags": flags}) + "\n")


_RES = re.compile(r"^RESULT: (MATCH|NO MATCH)\s+(\d+)/(\d+) words \(([\d.]+)%\)", re.M)
_STR = re.compile(r"^STRUCTURE: OP=(\d+) REG=(\d+) MOVED=(\d+)", re.M)
_IDN = re.compile(r"^IDENTITY: (.*)$", re.M)


def _run_checks(runs, cc, jobs):
    """runs: [(label, src, addr, flags)]. Run `fn.py check` for each as a subprocess (each appends its own
    check_log.jsonl line), in parallel. Returns rows sorted best first: dict(label, out, ok, key, ...)."""
    from concurrent.futures import ThreadPoolExecutor

    def one(run):
        label, src, addr, flags = run
        r = subprocess.run([sys.executable, os.path.abspath(__file__), "check", src, "%08X" % addr,
                            "--cc", cc, "--flags", flags], capture_output=True, text=True)
        out = r.stdout + (("\n" + r.stderr) if r.returncode and r.stderr else "")
        row = {"label": label, "out": out, "flags": flags}
        m, st = _RES.search(out), _STR.search(out)
        if r.returncode or not m or not st:
            lines = [x for x in out.splitlines() if x.strip() and x.strip() != "COMPILE ERROR"]
            err = next((x for x in lines if "Error" in x or "error" in x), lines[0] if lines else "(no output)")
            row.update(ok=False, err=err.strip(), key=(1,))
            return row
        match = m.group(1) == "MATCH"
        op, reg, moved = (int(x) for x in st.groups())
        idn = _IDN.search(out)
        idn = idn.group(1) if idn else ""
        bad = re.search(r"(\d+) MISMATCH", idn)
        row.update(ok=True, match=match, words=f"{m.group(2)}/{m.group(3)}", pct=float(m.group(4)),
                   op=op, reg=reg, moved=moved, ident=idn,
                   key=(0, not match, int(bad.group(1)) if bad else 0, op, reg + moved, -float(m.group(4))))
        return row

    with ThreadPoolExecutor(max_workers=max(1, jobs)) as ex:
        rows = list(ex.map(one, runs))
    rows.sort(key=lambda x: x["key"])  # stable: ties keep argument order
    return rows


def _print_ranked(rows):
    w = max(len(r["label"]) for r in rows)
    for r in rows:
        if r["ok"]:
            res = "MATCH   " if r["match"] else "NO MATCH"
            idn = f"  [IDENTITY {r['ident']}]" if r["match"] else ""
            print(f"{r['label']:{w}}  {res} {r['words']:>9} {r['pct']:5.1f}%  "
                  f"OP={r['op']} REG={r['reg']} MOVED={r['moved']}{idn}")
        else:
            print(f"{r['label']:{w}}  FAILED  {r['err']}")
    print("=" * 20 + f" best: {rows[0]['label']} " + "=" * 20)
    print(rows[0]["out"].rstrip())


def cmd_checks(addr, files, cc=DEFAULT_CC, flags=DEFAULT_FLAGS, jobs=8):
    _print_ranked(_run_checks([(f, f, addr, flags) for f in files], cc, int(jobs)))


def cmd_flags(src, addr, cc=DEFAULT_CC, base=DEFAULT_FLAGS, jobs=8):
    sys.modules.setdefault("fn", sys.modules[__name__])  # run as a script: let refine reuse this module
    import refine
    rows = _run_checks([(f, src, addr, f) for f in refine.flag_variants(base)], cc, int(jobs))
    _print_ranked(rows)
    print(f"BEST FLAGS: {rows[0]['flags']}")


if __name__ == "__main__":
    a = sys.argv[1:]
    if not a:
        print(__doc__)
        sys.exit(0)
    if a[0] == "show":
        cmd_show(int(a[1], 16))
    elif a[0] == "xref":
        cmd_xref(int(a[1], 16))
    elif a[0] == "check":
        kw = {}
        rest = a[3:]
        while rest:
            k, v = rest[0], rest[1]
            kw[k.lstrip("-")] = v
            rest = rest[2:]
        cmd_check(a[1], int(a[2], 16), **kw)
    elif a[0] in ("checks", "flags"):
        kw, pos = {}, []
        rest = a[1:]
        while rest:
            if rest[0].startswith("--"):
                kw[rest[0][2:]] = rest[1]
                rest = rest[2:]
            else:
                pos.append(rest[0])
                rest = rest[1:]
        if a[0] == "checks":
            cmd_checks(int(pos[0], 16), pos[1:], **kw)
        else:
            cmd_flags(pos[0], int(pos[1], 16), **kw)
