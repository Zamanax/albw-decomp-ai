"""Static-initializer generator for the fam_sti family (sti = a translation unit's __sti___ function).

    uv run python tools/stigen.py 0xADDR [--out FILE] [--check] [--events]

Reads the target in code.bin, emulates its straight-line code (literal loads, `add rX, pc, #`
string addresses, mov/mvn/orr/add/sub, str/strb/strh/strd/stm, ldr from ro data, VFP
vldr/vmov/vstr/vstm, calls) into a list of store and call events, groups the events into the
unit's globals in initialisation order and prints a C++ source that defines those globals in
that order. --out writes the source, --check also runs `fn.py check` on it, --events prints the
emulated events instead of a source.

Every global starts with the fam_sti prologue: `ldr r2, =data; mvn r0, #0; mov r1, r0; push;
strd` (an `s64 x = Id64().v;`), then a zero `Pair`. Forms it knows, each learnt from a matched
sibling (src/work8/fam_sti, src/work8/auto) or from a target that matched with it:

  Id64 at the anchor          `s64 data_X = Id64().v;`
  Id64 at anchor + N          `struct T_X { char pad[N]; s64 v; }; T_X data_X = { {0}, Id64().v };`
  Pair                        `Pair data_X;` (zero s64 through a constructor)
  SafeString                  `SafeString str_X("...");` (vtable 0x6F5988 + pointer into the
                              function's own pool, destructor 0x688D9C registered at exit)
  SafeString table            `SafeString strs_X[N] = {...};` (array destructor registered once)
  PtrList<N> + Factory        `PtrList<N> list_X; Factory factory_X(create, ro, "name", &list_X,
                              "jp name", a, b);` (constructor 0x... read from the call)
  Vec3 / float structs        `Vec3 data_X(x, y, z);` (a float run of whole triples is a row of
                              Vec3s, one vstm group each) / `struct T_X { f32 f0..; T_X() : ... {} };`
  f2l globals                 `static u32 data_X = (u32)f2l(K);` (__aeabi_f2lz with a constant)
                              and the constructor form `F2l data_X(K);` when the address is
                              derived from the previous object (the anchored-Id64 sub-family)
  byte/word constructors      `struct T_X { u8 m0..; T_X() : m0(..) {} };` (colour bytes,
                              u32 constants)
  extern-copy globals         `u32 data_X = ro_Y;` (value loaded from another unit's constant)
  constructor calls           `T data_X;` with an out-of-line constructor `func_X(this)` and an
                              optional destructor registration

The unit's strings are read back from the function's pool and written octal-escaped, so the
Shift-JIS bytes survive any source encoding.
"""
import argparse
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402

M32 = 0xFFFFFFFF
VT_SAFESTRING = 0x6F5988
DTOR_SAFESTRING = 0x688D9C
DSO_HANDLE = 0x100000
F2LZ = 0x114608
ATEXIT = 0x5902C0
VEC_DTOR = 0x100948  # __aeabi_vec_dtor (in the Thumb runtime block at 0x100110)
# Emission variant for constant structs (u8/u16/u32 runs): values passed as constructor parameters
# (`T data(c0, c1, ...);`) instead of the default member-init list. armcc allocates the argument
# values differently, which is what a few colour-struct targets need.
PARAM_CTOR = False
STACK = 0xF0000000  # the emulated sp: a fake range no global lives in


def is_stack(a):
    return isinstance(a, int) and STACK - 0x10000 <= a <= STACK


def ror(v, r):
    return ((v >> r) | (v << (32 - r))) & M32 if r else v


def dp_imm(w):
    return ror(w & 0xFF, 2 * ((w >> 8) & 0xF))


def f32(bits):
    return struct.unpack("<f", struct.pack("<I", bits & M32))[0]


class Sym:
    """A value the emulator cannot know: a call result or a load from writable memory."""

    def __init__(self, kind, *args):
        self.kind, self.args = kind, args

    def __repr__(self):
        return "%s(%s)" % (self.kind, ", ".join(hex(a) if isinstance(a, int) else repr(a) for a in self.args))


class Ev:
    """One emulated event: a store ('st'), a call ('call'), a linker-inlined call ('nop')."""

    def __init__(self, kind, pc, **kw):
        self.kind, self.pc = kind, pc
        self.__dict__.update(kw)

    def __repr__(self):
        d = {k: v for k, v in self.__dict__.items() if k not in ("kind", "pc")}
        def show(v):
            if isinstance(v, int):
                return hex(v)
            if isinstance(v, list):
                return "[" + ", ".join(show(x) for x in v) + "]"
            return repr(v)
        return "%08X %s %s" % (self.pc, self.kind, " ".join("%s=%s" % (k, show(v)) for k, v in d.items()))


def emulate(addr):
    """Emulate the straight-line static initializer at addr.

    Returns (events, info). Events, in program order: 'st' (addr, size, val, reg/sreg, base register,
    lit = pool address the base register was loaded from), 'call' (target, args r0-r3, sargs s0-s3,
    tail) and 'nop' (`mov r0, r0`: a call armlink inlined, with the r0-r3 it would have taken).
    A call leaves Sym('ret', target, r0) in r0: constructors return `this`, so a later store through
    r0 resolves to the object."""
    s, e = fn.func_range(addr)
    R = {13: STACK}  # core registers: int or Sym; sp points into a fake stack range
    S = {}       # VFP single registers: int bits or Sym
    lit = {}     # register -> pool address it was loaded from (anchor provenance)
    stk = {}     # stack memory: argument temporaries built for calls
    ev = []
    end = None
    seen = set()

    def base(n, o):
        v = R.get(n)
        if isinstance(v, Sym) and v.kind == "ret" and isinstance(v.args[1], int):
            v = v.args[1]  # a constructor's result is its `this`
        if not isinstance(v, int):
            raise ValueError("unknown base r%d at %08X" % (n, o))
        return v

    def store(o, a, size, val, **kw):
        if is_stack(a):
            stk[a] = val
        else:
            ev.append(Ev("st", o, addr=a, size=size, val=val, **kw))

    def load(a):
        if is_stack(a):
            return stk.get(a, Sym("ld", a))
        return Sym("ld", a)

    def call(o, t, tail):
        ev.append(Ev("call", o, target=t, args=[R.get(i) for i in range(4)],
                     sargs=[S.get(i) for i in range(4)], tail=tail, stack=dict(stk)))
        a0 = R.get(0)
        for i in (0, 1, 2, 3, 12, 14):
            R.pop(i, None)
            lit.pop(i, None)
        R[0] = Sym("ret", t, a0)
        R[1] = Sym("ret_hi", t)
        for i in range(16):
            S.pop(i, None)

    o = s
    while o < e:
        if o in seen:
            raise ValueError("loop at %08X" % o)
        seen.add(o)
        w = fn.rd32(o)
        cond = w >> 28
        nxt = o + 4
        if cond == 0xF and (w & 0x0E000000) == 0x0A000000:  # blx imm
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            call(o, (o + 8 + (imm << 2)) | ((w >> 23) & 2), False)
            o = nxt
            continue
        if cond != 0xE:
            raise ValueError("conditional instruction at %08X: %08X" % (o, w))
        if w == 0xE1A00000:  # mov r0, r0: a call armlink inlined (a NOP leaf, e.g. __aeabi_atexit)
            ev.append(Ev("nop", o, args=[R.get(i) for i in range(4)]))
        elif (w & 0x0E000000) == 0x0A000000:  # b / bl
            imm = w & 0xFFFFFF
            imm = imm - 0x1000000 if imm & 0x800000 else imm
            t = o + 8 + (imm << 2)
            link = bool(w & 0x01000000)
            if not link and s <= t < e:
                if t <= o:
                    raise ValueError("backward branch at %08X" % o)
                o = t  # jump over a mid-function literal pool
                continue
            call(o, t, not link)
            if not link:
                end = o
                break
        elif (w & 0xFFFF8000) == 0xE8BD8000 or w in (0xE12FFF1E, 0xE49DF004):  # pop {.., pc} / bx lr
            end = o
            break
        elif (w & 0x0FFF0000) == 0x092D0000:  # push: the saved registers are not globals
            R[13] -= 4 * bin(w & 0xFFFF).count("1")
        elif (w & 0x0FFF0000) == 0x08BD0000:  # pop without pc
            R[13] += 4 * bin(w & 0xFFFF).count("1")
        elif (w & 0x0FEF0000) == 0x028F0000 or (w & 0x0FEF0000) == 0x024F0000:  # adr
            d = (w >> 12) & 15
            v = dp_imm(w)
            R[d] = o + 8 + (v if (w & 0x0FEF0000) == 0x028F0000 else -v)
            lit.pop(d, None)
        elif (w & 0x0E000000) == 0x02000000:  # data processing, immediate
            op = (w >> 21) & 15
            n, d, v = (w >> 16) & 15, (w >> 12) & 15, dp_imm(w)
            a = R.get(n)
            if op == 13:
                R[d] = v
            elif op == 15:
                R[d] = ~v & M32
            elif isinstance(a, int):
                if op == 4:
                    R[d] = (a + v) & M32
                elif op == 2:
                    R[d] = (a - v) & M32
                elif op == 12:
                    R[d] = a | v
                elif op == 14:
                    R[d] = a & ~v & M32
                elif op == 0:
                    R[d] = a & v
                elif op == 1:
                    R[d] = a ^ v
                else:
                    raise ValueError("data-processing op %d at %08X" % (op, o))
            else:
                R[d] = Sym("alu", op, a, v)
            if op in (4, 2) and n in lit:
                lit[d] = lit[n]
            else:
                lit.pop(d, None)
        elif (w & 0x0FEF0FF0) == 0x01A00000:  # mov rd, rm
            d, m = (w >> 12) & 15, w & 15
            R[d] = R.get(m)
            if m in lit:
                lit[d] = lit[m]
            else:
                lit.pop(d, None)
        elif (w & 0x0E000000) == 0x04000000:  # ldr/str word/byte, immediate offset
            P, U, B, W, L = (w >> 24) & 1, (w >> 23) & 1, (w >> 22) & 1, (w >> 21) & 1, (w >> 20) & 1
            n, d, off = (w >> 16) & 15, (w >> 12) & 15, w & 0xFFF
            off = off if U else -off
            if n == 15:
                a = o + 8 + off
            else:
                b = base(n, o)
                a = (b + off) & M32 if P else b
                if W or not P:
                    R[n] = (b + off) & M32
            if L:
                if n == 15:
                    R[d] = fn.rd32(a)
                    lit[d] = a
                elif fn.in_ro(a) or fn.in_text(a):
                    v = fn.rd32(a & ~3)
                    R[d] = Sym("ldro", a, (v >> (8 * (a & 3))) & 0xFF if B else v)
                    lit.pop(d, None)
                else:
                    R[d] = load(a)
                    lit.pop(d, None)
            else:
                store(o, a, 1 if B else 4, R.get(d), reg=d, base=n, lit=lit.get(n))
        elif (w & 0x0E400090) == 0x00400090 and (w & 0x60):  # strh/strd/ldrd/ldrh, immediate offset
            P, U, W, L = (w >> 24) & 1, (w >> 23) & 1, (w >> 21) & 1, (w >> 20) & 1
            n, d = (w >> 16) & 15, (w >> 12) & 15
            off = ((w >> 4) & 0xF0) | (w & 0xF)
            off = off if U else -off
            sh = (w >> 5) & 3
            b = base(n, o)
            a = (b + off) & M32 if P else b
            if W or not P:
                R[n] = (b + off) & M32
            if not L and sh == 3:  # strd
                store(o, a, 4, R.get(d), reg=d, base=n, lit=lit.get(n), strd=1)
                store(o, a + 4, 4, R.get(d + 1), reg=d + 1, base=n, lit=lit.get(n), strd=2)
            elif not L and sh == 1:  # strh
                store(o, a, 2, R.get(d), reg=d, base=n, lit=lit.get(n))
            elif not L and sh == 2:  # ldrd
                R[d], R[d + 1] = load(a), load(a + 4)
            else:
                R[d] = load(a)
        elif (w & 0x0E000000) == 0x08000000:  # ldm/stm
            P, U, W, L = (w >> 24) & 1, (w >> 23) & 1, (w >> 21) & 1, (w >> 20) & 1
            n = (w >> 16) & 15
            regs = [r for r in range(16) if w >> r & 1]
            b = base(n, o)
            a = b + (4 if P else 0) if U else b - 4 * len(regs) + (0 if P else 4)
            for i, r in enumerate(regs):
                if L:
                    R[r] = load(a + 4 * i)
                else:
                    store(o, a + 4 * i, 4, R.get(r), reg=r, base=n, lit=lit.get(n), stm=len(regs))
            if W:
                R[n] = b + (4 if U else -4) * len(regs)
        elif (w & 0x0F200E00) == 0x0D000A00:  # vldr / vstr
            U, L, D = (w >> 23) & 1, (w >> 20) & 1, (w >> 22) & 1
            n, vd, dbl = (w >> 16) & 15, (w >> 12) & 15, (w >> 8) & 1
            off = (w & 0xFF) * 4
            off = off if U else -off
            a = o + 8 + off if n == 15 else (base(n, o) + off) & M32
            regs = [2 * (vd | D << 4), 2 * (vd | D << 4) + 1] if dbl else [vd << 1 | D]
            for i, sr in enumerate(regs):
                if L:
                    S[sr] = fn.rd32(a + 4 * i) if (fn.in_text(a) or fn.in_ro(a)) else load(a + 4 * i)
                else:
                    store(o, a + 4 * i, 4, S.get(sr), sreg=sr, base=n, lit=lit.get(n), vfp=1)
        elif (w & 0x0E000E00) == 0x0C000A00 and (w & 0x01A00000) != 0:  # vstm / vldm
            P, U, D, W, L = (w >> 24) & 1, (w >> 23) & 1, (w >> 22) & 1, (w >> 21) & 1, (w >> 20) & 1
            n, vd, dbl, cnt = (w >> 16) & 15, (w >> 12) & 15, (w >> 8) & 1, w & 0xFF
            b = base(n, o)
            first = 2 * (vd | D << 4) if dbl else (vd << 1 | D)
            a = b if U else b - 4 * cnt
            for i in range(cnt):
                if L:
                    S[first + i] = load(a + 4 * i)
                else:
                    store(o, a + 4 * i, 4, S.get(first + i), sreg=first + i, base=n, lit=lit.get(n), vfp=1, vstm=cnt)
            if W:
                R[n] = b + (4 if U else -4) * cnt
        elif (w & 0x0FB00EF0) == 0x0EB00A00:  # vmov.f32 sd, #imm
            D, vd = (w >> 22) & 1, (w >> 12) & 15
            imm8 = ((w >> 12) & 0xF0) | (w & 0xF)
            sign, b6 = imm8 >> 7, (imm8 >> 6) & 1
            exp = ((b6 ^ 1) << 7) | (0x7C if b6 else 0) | ((imm8 >> 4) & 3)
            S[vd << 1 | D] = (sign << 31) | (exp << 23) | ((imm8 & 0xF) << 19)
        elif (w & 0x0FF00F7F) == 0x0E000A10:  # vmov sn, rt
            nn, t, N = (w >> 16) & 15, (w >> 12) & 15, (w >> 7) & 1
            S[nn << 1 | N] = R.get(t)
        elif (w & 0x0FF00F7F) == 0x0E100A10:  # vmov rt, sn
            nn, t, N = (w >> 16) & 15, (w >> 12) & 15, (w >> 7) & 1
            R[t] = S.get(nn << 1 | N)
        elif (w & 0x0FBF0FD0) == 0x0EB00A40:  # vmov.f32 sd, sm
            D, vd, M, vm = (w >> 22) & 1, (w >> 12) & 15, (w >> 5) & 1, w & 15
            S[vd << 1 | D] = S.get(vm << 1 | M)
        else:
            raise ValueError("unhandled instruction at %08X: %08X" % (o, w))
        o = nxt
    return ev, {"start": s, "end": end, "range_end": e}


def cstr_at(p):
    """The NUL-terminated byte string at p in code.bin."""
    off = p - fn.TA
    z = fn.CODE.index(b"\0", off)
    return fn.CODE[off:z]


def c_literal(b):
    """A C string literal for raw bytes: printable ASCII kept, everything else octal-escaped."""
    out = []
    for c in b:
        if 32 <= c < 127 and chr(c) not in '"\\?':
            out.append(chr(c))
        else:
            out.append("\\%03o" % c)
    return '"' + "".join(out) + '"'


def string_at(v, fs, fe):
    """The literal bytes when v points into the function's own pool [fs, fe), else None."""
    if isinstance(v, int) and fs <= v < fe + 0x10000 and fn.in_text(v):
        try:
            return cstr_at(v)
        except ValueError:
            return None
    return None


def is_reg(x):
    """A destructor registration: __aeabi_atexit(obj, dtor, &__dso_handle), called or linker-inlined."""
    if x.kind not in ("call", "nop"):
        return False
    if x.kind == "call" and x.target != ATEXIT:
        return False
    return x.args[2] == DSO_HANDLE and isinstance(x.args[1], int) and fn.in_text(x.args[1])


class Glob:
    """One global of the unit: address, size, form and the events that initialise it."""

    def __init__(self, addr, size, kind, order, **kw):
        self.addr, self.size, self.kind, self.order = addr, size, kind, order
        self.__dict__.update(kw)

    @property
    def bss(self):
        return self.addr >= fn.DA + fn.DS

    def __repr__(self):
        return "%s@%08X+%d" % (self.kind, self.addr, self.size)


def analyze(addr):
    """Group the events of the static initializer at addr into the unit's globals, in initialisation
    order. Raises ValueError on a form this tool does not know."""
    ev, info = emulate(addr)
    fs, fe = info["start"], info["range_end"]
    st = [x for x in ev if x.kind == "st"]
    if len(st) < 4 or not (st[0].val == M32 and st[1].val == M32 and getattr(st[0], "strd", 0)):
        raise ValueError("no Id64 prologue")
    if not (st[2].val == 0 and st[3].val == 0 and st[3].addr == st[2].addr + 4):
        raise ValueError("no Pair after the Id64")
    globs = [Glob(st[0].addr, 8, "id64", 0, anchor=fn.rd32(st[0].lit), base=st[0].base),
             Glob(st[2].addr, 8, "pair", 1)]
    rest = ev[ev.index(st[3]) + 1:]

    slots = {}      # SafeString slot address -> [vtable event, string bytes]
    pending = []    # slot addresses (in first-store order) not yet closed by a registration
    loose = []      # other stores, in program order
    f2l = {}        # id(call event) -> constant argument
    n = 2

    def flush_loose():
        nonlocal n
        for g in group_loose(loose, f2l):
            g.order = n
            n += 1
            globs.append(g)
        loose.clear()

    for x in rest:
        if x.kind == "st":
            s = string_at(x.val, fs, fe)
            if x.val == VT_SAFESTRING:
                slots.setdefault(x.addr, [None, None])[0] = x
                if x.addr not in pending:
                    pending.append(x.addr)
            elif s is not None and (x.addr - 4 in slots or any(
                    y.kind == "st" and y.addr == x.addr - 4 and y.val == VT_SAFESTRING for y in rest)):
                slots.setdefault(x.addr - 4, [None, None])[1] = s
                if x.addr - 4 not in pending:
                    pending.append(x.addr - 4)
            else:
                loose.append(x)
        elif is_reg(x):
            obj, dtor = x.args[0], x.args[1]
            if dtor == DTOR_SAFESTRING and obj in slots:
                flush_loose()
                vt, s = slots.pop(obj)
                pending.remove(obj)
                if pending:
                    raise ValueError("SafeString %08X registered before %s" % (obj, pending))
                globs.append(Glob(obj, 8, "str", n, text=s))
                n += 1
            elif obj == 0 and pending:
                flush_loose()
                globs.append(table_glob(sorted(pending), slots, dtor, n))
                pending.clear()
                n += 1
            else:
                raise ValueError("registration of %r with %08X at %08X" % (obj, dtor, x.pc))
        elif x.kind == "call" and x.target == F2LZ:
            a0 = x.args[0]
            if not isinstance(a0, int):
                raise ValueError("f2lz of a non-constant at %08X" % x.pc)
            f2l[id(x)] = a0
            loose.append(x)
        else:
            raise ValueError("unhandled %s at %08X" % (x.kind, x.pc))
    if pending:
        raise ValueError("SafeStrings without a registration: %s" % pending)
    flush_loose()
    return globs, info


def vec_dtor_of(helper):
    """(array, element destructor, element size, count) of a unit's array-destructor helper: the
    function armcc registers with __aeabi_atexit for an array whose elements have destructors
    (`ldr r1, =dtor; ldr r0, =array; mov r3, #n; mov r2, #size; b __aeabi_vec_dtor`)."""
    try:
        ev, _ = emulate(helper)
    except ValueError:
        return None
    c = [x for x in ev if x.kind == "call"]
    if len(c) == 1 and c[0].target == VEC_DTOR and all(isinstance(v, int) for v in c[0].args):
        return tuple(c[0].args)
    return None


def table_glob(addrs, slots, dtor, order):
    """A SafeString array or a table of structs holding SafeStrings, from the slot addresses closed by
    one array-destructor registration. The registered helper names the array, the element destructor,
    the element size and the count; a table's other words are u32 fields whose values are read from
    the initial data image (zero in .bss)."""
    vd = vec_dtor_of(dtor)
    if vd is None:
        raise ValueError("registration helper %08X is not an array destructor" % dtor)
    base, edtor, size, count = vd
    if any(not base <= a < base + size * count for a in addrs):
        raise ValueError("SafeString slots outside the array %08X" % base)
    texts = {a: slots.pop(a)[1] for a in addrs}
    if edtor == DTOR_SAFESTRING and size == 8:
        if sorted(addrs) != [base + 8 * k for k in range(count)]:
            raise ValueError("SafeString array %08X has a hole" % base)
        return Glob(base, 8 * count, "strs", order, texts=[texts[a] for a in sorted(addrs)], adtor=dtor)
    per = sorted({(a - base) % size for a in addrs})
    if sorted(addrs) != sorted(base + k * size + p for k in range(count) for p in per):
        raise ValueError("SafeString table %08X is not periodic" % base)
    fields = []  # (offset in entry, 's' or 'w')
    o = 0
    while o < size:
        if o in per:
            fields.append((o, "s"))
            o += 8
        else:
            fields.append((o, "w"))
            o += 4
    if o != size:
        raise ValueError("SafeString table %08X: fields do not tile the element" % base)
    entries = []
    for k in range(count):
        row = []
        for off, kind in fields:
            a = base + k * size + off
            row.append(texts[a] if kind == "s" else (fn.rd32(a) if a < fn.DA + fn.DS else 0))
        entries.append(row)
    return Glob(base, size * count, "table", order, fields=fields, entries=entries, adtor=dtor, edtor=edtor)


def group_loose(loose, f2l):
    """Plain stores and f2lz calls between two SafeStrings, in program order: f2l results (one u32
    global per store), runs of loads from other units' constants (`ldro`), and runs of constant
    f32 / u8 / u16 / u32 stores. A run takes every following store of its kind that extends or fills
    it (the scheduler may reorder stores inside one object); each run becomes one object."""
    out = []
    k = None
    cur = None
    for x in loose:
        if x.kind == "call":
            k = f2l[id(x)]
            continue
        v = x.val
        if isinstance(v, Sym) and v.kind == "ret" and v.args[0] == F2LZ:
            out.append(Glob(x.addr, 4, "f2l", 0, k=k))
            cur = None
            continue
        if isinstance(v, Sym) and v.kind == "ldro":
            kind, v = "ldro", v.args[0]
        elif isinstance(v, int):
            kind = "f32" if getattr(x, "vfp", 0) else ("u8" if x.size == 1 else ("u16" if x.size == 2 else "u32"))
        else:
            raise ValueError("store of %r at %08X" % (v, x.pc))
        if cur is not None and cur.kind == kind and x.addr not in cur.mem and \
                cur.lo - x.size <= x.addr <= cur.hi:
            cur.mem[x.addr] = v
            cur.lo, cur.hi = min(cur.lo, x.addr), max(cur.hi, x.addr + x.size)
            continue
        cur = Glob(x.addr, 0, kind, 0, mem={x.addr: v}, unit=x.size)
        cur.lo, cur.hi = x.addr, x.addr + x.size
        out.append(cur)
    for g in out:
        if g.kind == "f2l":
            continue
        ks = sorted(g.mem)
        if ks != list(range(g.lo, g.hi, g.unit)):
            raise ValueError("run at %08X has holes" % g.lo)
        g.addr, g.size = g.lo, g.hi - g.lo
        g.vals = [g.mem[a] for a in ks]
        if g.kind == "ldro":
            g.srcs = g.vals
    # A float run of whole triples is a row of Vec3(x, y, z) objects (one vstm group each); a
    # byte run of whole quads is a row of 4-byte colour structs (each sorted as its own .data
    # object, e.g. 0x005CFE6C where four of them precede the Id64).
    split = []
    for g in out:
        if g.kind == "f32" and len(g.vals) % 3 == 0:
            for i in range(0, len(g.vals), 3):
                split.append(Glob(g.addr + 4 * i, 12, "vec3", 0, vals=g.vals[i:i + 3]))
        elif g.kind == "u8" and len(g.vals) % 4 == 0:
            for i in range(0, len(g.vals), 4):
                split.append(Glob(g.addr + i, 4, "u8", 0, vals=g.vals[i:i + 4]))
        else:
            split.append(g)
    return split


HEADER = """// static initializer of a fam_sti unit, generated by tools/stigen.py from the target's own code
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
inline s64 f2l(f32 f) { return (s64)f; }

#include "static_init.h"

"""


def f32_lit(bits):
    """Shortest float literal that reads back to exactly these bits."""
    x = f32(bits)
    for p in range(1, 18):
        t = "%.*g" % (p, x)
        if struct.pack("<f", float(t)) == struct.pack("<I", bits):
            break
    if "e" not in t and "." not in t and "inf" not in t and "nan" not in t:
        t += ".0"
    return t + "f"


def align_of(g):
    return 8 if g.kind == "id64" else (1 if g.kind == "u8" else (2 if g.kind == "u16" else 4))


def layout(globs, start, key):
    """Addresses armcc gives these objects (one section from `start`): sorted by `key`, stable."""
    out = {}
    a = start
    for g in sorted(globs, key=key):
        al = align_of(g)
        a = (a + al - 1) & ~(al - 1)
        out[g.addr] = a
        a += g.size
    return out


def name_of_glob(g):
    if g.kind == "str":
        return "str_%08X" % g.addr
    if g.kind == "strs":
        return "strs_%08X" % g.addr
    return "data_%08X" % g.addr


def emit(globs):
    """C++ source for the unit: type definitions, then the globals defined in initialisation order.
    Globals whose address order in their section differs from what armcc's data ordering would give
    (size-sorted .data, definition-ordered .bss) become static members of `struct Unit`, declared in
    address order (armcc lays static members out in declaration order, 0x005B8944)."""
    types, externs, defs = [], [], []
    data = [g for g in globs if not g.bss]
    bss = [g for g in globs if g.bss]
    idg = globs[0]
    anchor = idg.anchor
    pad = 0
    covered = [g for g in data if anchor <= g.addr < idg.addr]
    if anchor < idg.addr and not covered:
        pad = idg.addr - anchor
        data = [g for g in data if g is not idg]
    members = set()
    if data:
        lo = min(g.addr for g in data)
        want = {g.addr: g.addr for g in data}
        if layout(data, lo, key=lambda g: (g.size, g.order)) != want:
            members |= {id(g) for g in data}
    if bss:
        lo = min(g.addr for g in bss)
        if layout(bss, lo, key=lambda g: g.order) != {g.addr: g.addr for g in bss}:
            members |= {id(g) for g in bss}
    # The f2l form: when the anchor register is callee-saved (r4, loaded before the Id64 store and
    # kept across the f2lz calls) each result is stored through it, as a plain `u32 x = (u32)f2l(K)`
    # does (0x005CFA14). Otherwise the store goes through a `this` computed before the call: a class
    # whose constructor converts (`F2l x(K)`; 0x005B7FAC, the anchored-Id64 sub-family).
    f2l_ctor = idg.base != 4

    def decl(g):
        """(type, declarator) of a global."""
        nm = name_of_glob(g)
        if g.kind == "id64":
            if pad:
                return "T_%08X" % anchor, "data_%08X" % anchor
            return "s64", nm
        if g.kind == "pair":
            return "Pair", nm
        if g.kind == "str":
            return "SafeString", nm
        if g.kind == "strs":
            return "SafeString", "%s[%d]" % (nm, len(g.texts))
        if g.kind == "f2l":
            return ("F2l" if f2l_ctor else "u32"), nm
        if g.kind == "ldro":
            return "u32", nm if len(g.srcs) == 1 else "%s[%d]" % (nm, len(g.srcs))
        if g.kind == "table":
            return "E_%08X" % g.edtor, "%s[%d]" % (nm, len(g.entries))
        if g.kind == "vec3":
            return "Vec3", nm
        return "T_%08X" % g.addr, nm

    def init(g):
        """The initialiser written after the declarator (with its leading ' = ' / '(')."""
        if g.kind == "id64":
            return " = { {0}, Id64().v }" if pad else " = Id64().v"
        if g.kind == "vec3":
            return "(%s)" % ", ".join(f32_lit(v) for v in g.vals)
        if g.kind == "str":
            return "(%s)" % c_literal(g.text)
        if g.kind == "strs":
            return " = {\n" + ",\n".join("    " + c_literal(t) for t in g.texts) + "\n}"
        if g.kind == "f2l":
            return "(%s)" % f32_lit(g.k) if f2l_ctor else " = (u32)f2l(%s)" % f32_lit(g.k)
        if g.kind == "ldro":
            if len(g.srcs) == 1:
                return " = ro_%08X" % g.srcs[0]
            return " = { %s }" % ", ".join("ro_%08X" % s for s in g.srcs)
        if g.kind == "table":
            rows = []
            for row in g.entries:
                rows.append("    { %s }" % ", ".join(
                    c_literal(v) if kind == "s" else "0x%x" % v for v, (off, kind) in zip(row, g.fields)))
            return " = {\n" + ",\n".join(rows) + "\n}"
        if PARAM_CTOR and g.kind in ("u8", "u16", "u32"):
            return "(%s)" % ", ".join("0x%x" % v for v in g.vals)
        return ""

    for g in globs:
        if g.kind == "id64" and pad:
            types.append("#pragma pack(4)\nstruct T_%08X { char pad[%d]; s64 v; };\n#pragma pack()" % (anchor, pad))
        elif g.kind == "ldro":
            externs.extend("extern const u32 ro_%08X;" % s for s in g.srcs if
                           "extern const u32 ro_%08X;" % s not in externs)
        elif g.kind == "table":
            t = ("// element destructor 0x%08X is out of line (a `bx lr` copy armlink kept)\n"
                 "struct E_%08X { %s; ~E_%08X(); };" % (g.edtor, g.edtor, "; ".join(
                     "%s m%d" % ("SafeString" if kind == "s" else "u32", i) for i, (off, kind) in enumerate(g.fields)),
                     g.edtor))
            if t not in types:
                types.append(t)
        elif g.kind == "f2l" and f2l_ctor:
            t = "struct F2l { u32 v; F2l(f32 f) : v((u32)f2l(f)) {} };"
            if t not in types:
                types.append(t)
        elif g.kind == "vec3":
            if '#include "vec3.h"' not in types:
                types.insert(0, '#include "vec3.h"')
        elif g.kind in ("f32", "u8", "u16", "u32"):
            ty = {"f32": "f32", "u8": "u8", "u16": "u16", "u32": "u32"}[g.kind]
            names = ["m%d" % i for i in range(len(g.vals))]
            vals = [f32_lit(v) if g.kind == "f32" else "0x%x" % v for v in g.vals]
            if PARAM_CTOR and g.kind in ("u8", "u16", "u32"):
                args = ["a%d" % i for i in range(len(g.vals))]
                types.append("struct T_%08X { %s; T_%08X(%s) : %s {} };" % (
                    g.addr, "; ".join("%s %s" % (ty, m) for m in names), g.addr,
                    ", ".join("%s %s" % (ty, a) for a in args),
                    ", ".join("%s(%s)" % (m, a) for m, a in zip(names, args))))
            else:
                types.append("struct T_%08X { %s; T_%08X() : %s {} };" % (
                    g.addr, "; ".join("%s %s" % (ty, m) for m in names), g.addr,
                    ", ".join("%s(%s)" % (m, v) for m, v in zip(names, vals))))
    unit = [g for g in sorted(globs, key=lambda g: g.addr) if id(g) in members]
    if unit:
        body = "".join("    static %s %s;\n" % decl(g) for g in unit)
        types.append("struct Unit {\n%s};" % body)
    for g in globs:
        ty, d = decl(g)
        if id(g) in members:
            d = "Unit::" + d
        defs.append("%s %s%s;" % (ty, d, init(g)))
    src = HEADER
    if types:
        src += "\n".join(types) + "\n"
    if externs:
        src += "\n".join(externs) + "\n"
    src += "\n" + "\n".join(defs) + "\n"
    return src


def generate(addr):
    """The C++ source for the static initializer at addr (raises ValueError on an unknown form)."""
    globs, info = analyze(addr)
    return emit(globs)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr")
    ap.add_argument("--out", help="write the source here (default: print it)")
    ap.add_argument("--check", action="store_true", help="run fn.py check on --out")
    ap.add_argument("--events", action="store_true", help="print the emulated events and the globals")
    a = ap.parse_args(argv)
    addr = int(a.addr, 16)
    if a.events:
        ev, info = emulate(addr)
        for x in ev:
            print(x)
        for g in analyze(addr)[0]:
            print(g)
        return
    src = generate(addr)
    if not a.out:
        sys.stdout.write(src)
        if a.check:
            sys.exit("--check needs --out")
        return
    with open(a.out, "w", encoding="ascii", newline="\n") as fh:
        fh.write(src)
    print("wrote %s" % a.out)
    if a.check:
        r = subprocess.run([sys.executable, os.path.join(fn.ROOT, "tools", "fn.py"), "check", a.out, "0x%08X" % addr],
                           capture_output=True, text=True)
        sys.stdout.write(r.stdout + r.stderr)


if __name__ == "__main__":
    main()
