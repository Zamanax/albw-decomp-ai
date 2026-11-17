#!/usr/bin/env python
"""Register-allocation probes: measure what source shape decides a callee-saved register.

  uv run python tools/regalloc.py alloc PROBE.cpp FN member=index ...   [--opt O3|O2]
  uv run python tools/regalloc.py alias SRC.cpp ADDR [--apply]

alloc compiles PROBE.cpp with armcc -S (no game binary needed) and prints which callee-saved
register each value landed in. A probe writes each value once as `g-><name> = <value>;` into a
struct whose member name is the value's name; with calls between the stores so they cannot merge,
the STR offsets name the values.

What the probes established (2026-11-17, -O3 -Otime unless noted):

  * callee-saved registers are filled in live-range start order: parameters first among equal
    values, then locals in declaration order. Two locals declared before the parameters' first use
    take r4/r5 (`const void* k = &K::s; void* z = 0;` -> k=r4, z=r5), pushing the parameters to r6/r7.
  * a constant address is promoted to a register when it has a live range; a *local* initialised
    from it takes the earlier register (`both_locals`: p=r4, q=r5, then k=r6).
  * `u8`/`bool` zeros are rematerialised (`mov r0,#0`) at each store; they are not kept in a register.
  * a parameter that needs a later register can be moved up by aliasing it: in 002327BC at -O2,
    `Holder* hh = h;` first in the body then using `hh` everywhere turns `h = r6` into `h = r5`
    (the target's allocation) and takes the function from OP=1 REG=6 to OP=1 REG=1, 89 %

alias applies the second rule mechanically: the first pointer parameter of the function whose
address is ADDR becomes a local of the same type, used everywhere in that function, declared first
(and, as the second candidate, after the leading declarations). Both candidates are scored with
fn.py check and printed; --apply keeps the best one only if it improves the structure score.

Limit: the alias transform cannot change a register that is decided by a value's lifetime (a load
reused across a call), and it does not model the member-pointer/constant-pool offsets a TU sets.
"""
import argparse
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ARMCC = os.path.join(ROOT, "tools", "armcc", "4.1", "b1049", "bin", "armcc.exe")
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
OPT = {"O3": "-O3 -Otime", "O2": "-O2 -Otime"}
SIG = re.compile(r"^[A-Za-z_][\w:<>* ]*?\b(\w+)\s*\(\s*(?:struct\s+)?(\w+)\s*\*\s*(\w+)\s*\)\s*\{", re.M)
SCORE = re.compile(r"RESULT: (\w+ ?\w*)\s+(\d+)/(\d+).*?STRUCTURE: OP=(\d+) REG=(\d+) MOVED=(\d+)", re.S)


def alloc(probe, fname, members, opt="O3"):
    s = os.path.join(ROOT, "logs", "regalloc", "probe.s")
    args = [ARMCC, "-S", "--cpp", "--cpu=MPCore", "--fpmode=fast", "--apcs=/interwork"]
    args += OPT[opt].split() + ["--split_sections", "-I", os.path.join(ROOT, "shared", "include"),
                               probe, "-o", s]
    r = subprocess.run(args, capture_output=True, text=True)
    if r.returncode:
        return {"err": (r.stdout + r.stderr).strip()[:400]}
    txt = open(s).read()
    m = re.search(r"^\|*%s\|* PROC(.*?)^\s+ENDP" % re.escape(fname), txt, re.S | re.M | re.I)
    if not m:
        return {"err": "function not emitted"}
    body = m.group(1)
    push = re.search(r"PUSH\s+\{([^}]*)\}", body)
    regs = {}
    for mem, idx in members.items():
        mm = re.search(r"STR\w*\s+(r\d+),\[r\d+,#%d\]" % (4 * idx), body)
        if mm:
            regs[mem] = mm.group(1)
    return {"push": push.group(1).strip() if push else "", "regs": regs}


def score(path, addr, flags):
    out = subprocess.run(["uv", "run", "python", os.path.join(ROOT, "tools", "fn.py"), "check", path,
                          "0x%08X" % addr, "--flags", flags], capture_output=True, text=True).stdout
    m = SCORE.search(out)
    if not m:
        return None
    return dict(ok=m.group(1) == "MATCH", words="%s/%s" % (m.group(2), m.group(3)),
                op=int(m.group(4)), reg=int(m.group(5)), moved=int(m.group(6)))


def alias_variants(src):
    """(name, source) for the parameter-alias forms of the first pointer-parameter function."""
    m = SIG.search(src)
    if not m:
        return []
    ptype, pname = m.group(2), m.group(3)
    a = "%s_" % pname
    head = m.end()
    try:
        tail = src.index("\n}", head)
    except ValueError:
        return []
    body = src[head:tail]
    if re.search(r"\b%s_\w*\b" % pname, src):
        return []
    renamed = re.sub(r"\b%s\b" % pname, a, body)
    decl = "    %s* %s = %s;\n" % (ptype, a, pname)
    out = [("alias_first", src[:head] + "\n" + decl + renamed + src[tail:])]
    lines = body.split("\n")
    k = 0
    while k < len(lines) and (not lines[k].strip() or re.match(
            r"\s*(?:const\s+)?(?:Vec3|f32|s32|u32|u8|bool|void|char|Mdl|Actor|Npc|Self|Msg)\b\s*\**\s*[a-z]\w*\s*=",
            lines[k])):
        k += 1
    out.append(("alias_after", src[:head] + "\n" + "\n".join(lines[:k] + [decl.rstrip("\n")] + lines[k:]) + src[tail:]))
    return out


def cmd_alias(a):
    src = open(a.src, encoding="utf-8").read()
    flags = a.flags or DEFAULT_FLAGS
    base = score(a.src, a.addr, flags)
    if base is None:
        print("base: COMPILE ERROR")
        return 1
    print("base      %s OP=%d REG=%d MOVED=%d" % (base["words"], base["op"], base["reg"], base["moved"]))
    best, best_path = base, a.src
    for name, text in alias_variants(src):
        p = os.path.join(ROOT, "logs", "regalloc", "alias_%08X_%s%s" % (a.addr, name, os.path.splitext(a.src)[1]))
        open(p, "w", encoding="utf-8").write(text)
        r = score(p, a.addr, flags)
        if r is None:
            print("%-9s COMPILE ERROR" % name)
            continue
        print("%-9s %s OP=%d REG=%d MOVED=%d %s" % (name, r["words"], r["op"], r["reg"], r["moved"],
                                                   "(match)" if r["ok"] else ""))
        if (r["op"], r["reg"] + r["moved"]) < (best["op"], best["reg"] + best["moved"]):
            best, best_path = r, p
    if a.apply and best_path != a.src:
        open(a.src, "w", encoding="utf-8").write(open(best_path, encoding="utf-8").read())
        print("applied", best_path, "->", a.src)
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p1 = sub.add_parser("alloc", help="which registers does a probe source use?")
    p1.add_argument("probe")
    p1.add_argument("fn")
    p1.add_argument("members", nargs="+", help="member=index")
    p1.add_argument("--opt", default="O3", choices=sorted(OPT))
    p2 = sub.add_parser("alias", help="score parameter-alias variants of a source against its target")
    p2.add_argument("src")
    p2.add_argument("addr", type=lambda x: int(x, 16))
    p2.add_argument("--flags", default=None)
    p2.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    if a.cmd == "alloc":
        print(alloc(a.probe, a.fn, {k: int(v) for k, v in (x.split("=") for x in a.members)}, a.opt))
        return 0
    return cmd_alias(a)


if __name__ == "__main__":
    sys.exit(main())
