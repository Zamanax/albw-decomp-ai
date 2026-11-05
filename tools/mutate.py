#!/usr/bin/env python
"""Automatic source mutator: hill-climb source rewrites against the structural score.

  uv run python tools/mutate.py <addr> [--src FILE] [--flags F] [--budget 5000] [--minutes 0]
                                       [--jobs 16] [--seed 1] [--patience 300] [--register] [--dehack]
  uv run python tools/mutate.py queue    [--limit N] [--again] [same search options]
  uv run python tools/mutate.py barriers [--limit N] [--again] [same search options]
  uv run python tools/mutate.py tidy     [--register]

queue runs logs/campaign/search_queue.jsonl (campaign.py next writes it); barriers runs the
__schedule_barrier hacks listed in shared/wip/P2_schedule_barrier/remaining_final.json from their
own source with the barrier deleted (--dehack), so a MATCH is an honest replacement of the hack.

The start is --src (else the best source structscore knows for the address: refine's, the agents'
or shared/wip's). Every variant applies 1-3 random rewrites to the current state and is scored by
fn.py check's STRUCTURE line: fewest OP, then fewest REG+MOVED, then most matching words. A variant
that scores no worse replaces the current state (sideways moves cross plateaus); after --patience
checks without a new best the walk restarts from one of the best states seen.

Rewrites (token/statement level; C and C++). Only the compared function's body and the bodies of the
functions it calls that the file defines are rewritten:
  swap      move a statement one to three places within its block (declarations included)
  flip      if (c) A else B  ->  if (!c) B else A   (comparison inverted when it is the whole test)
  commute   swap the operands of + * & | ^ == != (precedence-aware), && || when both sides are
            free of calls and assignments
  temp      hoist a member-access chain or call result into a named, used local:
            T t = p->a; ... t->b ...   or   T* t = &p->a; ... t->b ...   (T from a compiler probe:
            armcc's "cannot initialize" error names the type of any expression in scope)
  inline    replace the single use of a local with its initialiser and drop the declaration
  helper    switch between the shared library's twin helpers (set/setCopy, exec/execute,
            PtrList/PtrListNamed/PtrListAssign, PtrListBase/...Named/...Assign)
  chain     a = K; b = K;  <->  a = b = K;   (K a literal or a plain name)
  nest      if (a && b) S  ->  if (a) { if (b) S }   (no else)
  retype    an integer type word in the body or parameter list -> the other signedness or a full
            word (int/u32/s32, u8/s8, u16/s16): the one rewrite that may change meaning
  flags     another of refine.flag_variants (-O2, -O3 without -Otime, -Ono_tailcall, fpic, Cortex-A9)
No rewrite produces an AGENTS.md forbidden construct; every new local is assigned and read. The
search does not need every step to keep the meaning: a byte-identical result computes what the
original computes, whatever path led there. --register sends a MATCH through worklist.py register
(re-verification + construct gates).

Output: logs/mutate/<ADDR>/  start.*, best.*, match.* (on MATCH), score.jsonl (every new best),
result.json (status MATCH | IDENTITY | EXHAUSTED, checks, start/best structure, flags, fanout).
campaign.py next drops EXHAUSTED functions from the search queue (they go back to the paid tiers).
"""
import argparse
import hashlib
import json
import os
import random
import re
import subprocess
import sys
import time
from concurrent.futures import FIRST_COMPLETED, ThreadPoolExecutor, wait

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import structscore  # noqa: E402

ROOT = structscore.ROOT
OUT = structscore.MUTATE
PY = sys.executable

# ------------------------------------------------------------------ tokens

TOKEN_RE = re.compile(r"""
 (?P<ws>\s+)
|(?P<com>//[^\n]*|/\*.*?\*/)
|(?P<str>"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*')
|(?P<num>(?:0[xX][0-9a-fA-F]+|\d+\.?\d*(?:[eE][+-]?\d+)?|\.\d+(?:[eE][+-]?\d+)?)[uUlLfF]*)
|(?P<id>[A-Za-z_]\w*)
|(?P<op>>>=|<<=|->\*|\.\.\.|::|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=|[-+*/%&|^!~<>=?:;,.()\[\]{}\#\\@$`])
""", re.S | re.X)
KEYWORDS = {"if", "else", "for", "while", "do", "switch", "case", "default", "return", "break", "continue",
            "goto", "sizeof", "new", "delete", "struct", "class", "union", "enum", "typedef", "static",
            "const", "volatile", "unsigned", "signed", "int", "char", "short", "long", "float", "double",
            "void", "bool", "inline", "extern", "operator", "template", "typename", "this", "true", "false"}
ASSIGN = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="}
PREC = {"*": 13, "/": 13, "%": 13, "+": 12, "-": 12, "<<": 11, ">>": 11, "<": 10, ">": 10, "<=": 10,
        ">=": 10, "==": 9, "!=": 9, "&": 8, "^": 7, "|": 6, "&&": 5, "||": 4}
COMMUTE = {"*": {"*"}, "+": {"+", "-"}, "&": {"&"}, "^": {"^"}, "|": {"|"}, "==": set(), "!=": set(),
           "&&": {"&&"}, "||": {"||"}}
STOP = {";", ",", "?", ":", "{", "}", "return", "case"} | ASSIGN
NEGATE = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
HELPERS = [("set", "setCopy"), ("exec", "execute"), ("PtrList", "PtrListNamed", "PtrListAssign"),
           ("PtrListBase", "PtrListBaseNamed", "PtrListBaseAssign")]
TYPE_HELPERS = {"PtrList", "PtrListNamed", "PtrListAssign", "PtrListBase", "PtrListBaseNamed", "PtrListBaseAssign"}
BARRIER_RE = re.compile(r"__schedule_barrier\s*\(\s*\)\s*;?")
BARRIERS = os.path.join(ROOT, "shared", "wip", "P2_schedule_barrier", "remaining_final.json")


def tokenize(text):
    """[(kind, text)]; preprocessor lines are one 'pp' token. ''.join(t for _, t in toks) == text."""
    toks, i, bol = [], 0, True
    while i < len(text):
        if bol and text[i] == "#":
            j = i
            while True:
                k = text.find("\n", j)
                if k < 0:
                    k = len(text)
                    break
                if text[k - 1] != "\\":
                    break
                j = k + 1
            toks.append(("pp", text[i:k]))
            i = k
            continue
        m = TOKEN_RE.match(text, i)
        if not m:
            toks.append(("op", text[i]))
            i += 1
            continue
        kind = m.lastgroup
        toks.append((kind, m.group()))
        if kind == "ws":
            bol = "\n" in m.group() or bol
        elif kind != "com":
            bol = False
        i = m.end()
    return toks


class Src:
    """Tokens, significant-token view, bracket matching, function bodies and their statement trees.
    focus: names of the functions whose bodies are parsed into statements (and so mutated); None = all."""

    def __init__(self, text, focus=None):
        self.text = text
        self.toks = tokenize(text)
        self.S = [i for i, (k, _) in enumerate(self.toks) if k not in ("ws", "com", "pp")]
        self.t = [self.toks[i][1] for i in self.S]
        self.match = {}
        stack = []
        for j, t in enumerate(self.t):
            if t in "([{" and len(t) == 1:
                stack.append(j)
            elif t in ")]}" and len(t) == 1 and stack:
                o = stack.pop()
                self.match[o], self.match[j] = j, o
        self.bodies = []  # (open, close) significant indices of function bodies
        j = 0
        while j < len(self.t):
            if self.t[j] == "{" and j in self.match and j > 0 and self.t[j - 1] in (")", "const"):
                self.bodies.append((j, self.match[j]))
                j = self.match[j]
            j += 1
        self.names = [self.body_name(o) for o, _ in self.bodies]
        self.active = [n for n, name in enumerate(self.names) if focus is None or name in focus]
        self.blocks = []  # every statement list of the active bodies: [Stmt]
        self.funcs = [self.parse_block(self.bodies[n][0] + 1, self.bodies[n][1]) for n in self.active]

    def body_name(self, o):
        """Name of the function whose body opens at o (constructor initialiser lists skipped)."""
        t, j = self.t, o - 1
        if t[j] == "const":
            j -= 1
        while j > 0 and t[j] == ")" and j in self.match:
            p = self.match[j]
            if p >= 2 and t[p - 2] in (",", ":"):  # `: a(x), b(y) {`: an initialiser, keep walking back
                j = p - 3
                continue
            return t[p - 1] if p >= 1 else None
        return None

    # rendering helpers ------------------------------------------------------
    def span(self, a, b):
        """Source text of significant tokens a..b inclusive (inner whitespace kept)."""
        return "".join(t for _, t in self.toks[self.S[a]:self.S[b] + 1])

    def splice(self, a, b, new):
        """Text with significant tokens a..b inclusive replaced by new."""
        return ("".join(t for _, t in self.toks[:self.S[a]]) + new +
                "".join(t for _, t in self.toks[self.S[b] + 1:]))

    def indent(self, a):
        """Whitespace that starts the line of significant token a."""
        i = self.S[a] - 1
        while i >= 0 and self.toks[i][0] == "ws" and "\n" not in self.toks[i][1]:
            i -= 1
        if i >= 0 and self.toks[i][0] == "ws":
            return self.toks[i][1].rsplit("\n", 1)[1]
        return ""

    # statements -------------------------------------------------------------
    def parse_block(self, lo, hi):
        out, j = [], lo
        while j < hi:
            st = self.parse_stmt(j, hi)
            if st is None:
                break
            out.append(st)
            j = st["end"] + 1
        self.blocks.append(out)
        return out

    def parse_stmt(self, j, hi):
        t = self.t
        w = t[j]
        if w == "{":
            c = self.match.get(j)
            if c is None:
                return None
            return dict(kind="block", start=j, end=c, kids=[self.parse_block(j + 1, c)])
        if w in ("if", "for", "while", "switch") and j + 1 < hi and t[j + 1] == "(" and j + 1 in self.match:
            c = self.match[j + 1]
            body = self.parse_stmt(c + 1, hi)
            if body is None:
                return None
            st = dict(kind="if" if w == "if" else "loop", start=j, end=body["end"], cond=(j + 1, c), then=body,
                      kids=[])
            if w == "if" and body["end"] + 1 < hi and t[body["end"] + 1] == "else":
                els = self.parse_stmt(body["end"] + 2, hi)
                if els is None:
                    return None
                st.update(els=els, end=els["end"])
            return st
        if w == "do":
            body = self.parse_stmt(j + 1, hi)
            if body is None:
                return None
            k = body["end"] + 1
            while k < hi and t[k] != ";":
                k = self.match.get(k, k) + 1 if t[k] in "([" else k + 1
            return dict(kind="loop", start=j, end=k, kids=[])
        if w in ("case", "default") or (w not in KEYWORDS and j + 1 < hi and t[j + 1] == ":"):
            k = j
            while k < hi and t[k] != ":":
                k += 1
            return dict(kind="label", start=j, end=k, kids=[])
        k = j
        while k < hi and t[k] != ";":
            if t[k] in ("(", "[", "{") and k in self.match:
                k = self.match[k]
            k += 1
        if k >= hi:
            return None
        kind = "jump" if w in ("return", "break", "continue", "goto") else "empty" if k == j else "simple"
        return dict(kind=kind, start=j, end=k, kids=[])

    def stmts(self):
        """Every statement with its block and position: (block, index, stmt)."""
        for b in self.blocks:
            for i, s in enumerate(b):
                yield b, i, s

    def func_of(self, j):
        for n, (o, c) in enumerate(self.bodies):
            if o < j < c:
                return n
        return None


def focus_names(text, target):
    """Names of the bodies to mutate: the function fn.py compared (its mangled or plain name `target`)
    and every function defined in the file that it calls, transitively. None when not found (= all)."""
    src = Src(text)
    parts = set(re.findall(r"\d+([A-Za-z_]\w*)", target)) | {target}
    names = {n for n in src.names if n and any(p == n or p.startswith(n) and p[len(n):].isdigit() for p in parts)}
    if not names:
        return None
    todo = list(names)
    while todo:
        n = todo.pop()
        for k, name in enumerate(src.names):
            if name != n:
                continue
            o, c = src.bodies[k]
            for j in range(o + 1, c):
                if src.t[j + 1] == "(" and src.t[j] in src.names and src.t[j] not in names:
                    names.add(src.t[j])
                    todo.append(src.t[j])
    return names


# ------------------------------------------------------------------ rewrites

MOVABLE = ("simple", "if", "loop", "block")


def m_swap(src, rng):
    cands = [(b, i) for b in src.blocks for i in range(len(b) - 1)
             if b[i]["kind"] in MOVABLE and b[i + 1]["kind"] in MOVABLE]
    if not cands:
        return None
    b, i = rng.choice(cands)
    d = 1
    while d < 3 and i + d + 1 < len(b) and b[i + d + 1]["kind"] in MOVABLE and rng.random() < 0.3:
        d += 1
    a, z = b[i], b[i + d]
    lo, hi = a["start"], z["end"]
    moved = src.span(a["start"], a["end"])
    rest = src.span(b[i + 1]["start"], z["end"])
    gap = "".join(t for _, t in src.toks[src.S[a["end"]] + 1:src.S[b[i + 1]["start"]]])
    if rng.random() < 0.5:   # move a down past the next d statements
        new = rest + gap + moved
    else:                    # move z up before a
        z_txt = src.span(z["start"], z["end"])
        mid = src.span(a["start"], b[i + d - 1]["end"])
        gap2 = "".join(t for _, t in src.toks[src.S[b[i + d - 1]["end"]] + 1:src.S[z["start"]]])
        new = z_txt + gap2 + mid
    return src.splice(lo, hi, new)


def negate_cond(src, a, c):
    """Text of the negation of the condition between parens a..c (exclusive)."""
    t = src.t
    inner = src.span(a + 1, c - 1)
    if t[a + 1] == "!" and (c - 1 == a + 2 or (t[a + 2] == "(" and src.match.get(a + 2) == c - 1)):
        return src.span(a + 2, c - 1)
    depth, ops = 0, []
    for k in range(a + 1, c):
        if t[k] in "([":
            depth += 1
        elif t[k] in ")]":
            depth -= 1
        elif depth == 0 and (t[k] in PREC and PREC[t[k]] <= 10 or t[k] in ASSIGN or t[k] == "?"):
            ops.append(k)
    if len(ops) == 1 and t[ops[0]] in NEGATE:
        k = ops[0]
        return src.span(a + 1, k - 1) + " " + NEGATE[t[k]] + " " + src.span(k + 1, c - 1)
    return "!(" + inner + ")"


def m_flip(src, rng):
    cands = [s for _, _, s in src.stmts() if s["kind"] == "if" and "els" in s and s["els"]["kind"] != "if"]
    if not cands:
        return None
    s = rng.choice(cands)
    a, c = s["cond"]
    th, el = s["then"], s["els"]
    wrap = lambda st: src.span(st["start"], st["end"]) if st["kind"] == "block" else \
        "{ " + src.span(st["start"], st["end"]) + " }"
    new = "if (" + negate_cond(src, a, c) + ") " + wrap(el) + " else " + wrap(th)
    return src.splice(s["start"], s["end"], new)


def operand_end(t, j):
    return j >= 0 and (t[j] in (")", "]") or (re.match(r"[\w\"']", t[j]) and t[j] not in ("return", "case", "sizeof")))


def m_commute(src, rng):
    t = src.t
    cands = [k for n in src.active for k in range(src.bodies[n][0] + 1, src.bodies[n][1])
             if t[k] in COMMUTE and operand_end(t, k - 1)]
    rng.shuffle(cands)
    for k in cands[:20]:
        op, P = t[k], PREC[t[k]]
        j = k - 1
        while True:  # left operand: higher precedence, or same level when regrouping keeps the value
            w = t[j]
            if w in (")", "]"):
                j = src.match.get(j, j) - 1
                continue
            if w in ("(", "[") or w in STOP:
                break
            if w in PREC and operand_end(t, j - 1):
                if PREC[w] > P or (PREC[w] == P and w in COMMUTE[op]):
                    j -= 1
                    continue
                break
            j -= 1
        L0 = j + 1
        j = k + 1
        while True:  # right operand: strictly higher precedence
            w = t[j]
            if w in ("(", "["):
                j = src.match.get(j, j) + 1
                continue
            if w in (")", "]") or w in STOP:
                break
            if w in PREC and operand_end(t, j - 1):
                if PREC[w] > P:
                    j += 1
                    continue
                break
            j += 1
        R1 = j - 1
        if L0 > k - 1 or R1 < k + 1:
            continue
        if op in ("*", "&") and L0 == k - 1 and R1 == k + 1 and t[L0 - 1] in (";", "{", "}", "(", ",", ":", "const") \
                and t[R1 + 1] in ("=", ";", ",", ")", "["):
            continue  # `T* x = ...` / `T& r`: a declaration, not a product
        if op in ("&&", "||"):
            side = t[L0:R1 + 1]
            if any(x in ASSIGN or x in ("++", "--") for x in side) or any(
                    side[i] == "(" and i > 0 and re.match(r"\w", side[i - 1]) for i in range(len(side))):
                continue
        ws_l = "".join(x for _, x in src.toks[src.S[k - 1] + 1:src.S[k]])
        ws_r = "".join(x for _, x in src.toks[src.S[k] + 1:src.S[k + 1]])
        return src.splice(L0, R1, src.span(k + 1, R1) + ws_l + op + ws_r + src.span(L0, k - 1))
    return None


def is_name(w):
    return re.match(r"[A-Za-z_]", w) is not None and (w not in KEYWORDS or w == "this")


def chains(src, lo, hi):
    """Candidate sub-expressions in significant tokens lo..hi, as (start, end): every member-access chain
    (p->a, p->a.b, this->m, m.x[i]) and every prefix of one followed by . or ->, and calls whose result
    is used inside an expression (f(x) + 1, p->get()->m)."""
    t, out = src.t, set()
    for j in range(lo, hi + 1):
        if not is_name(t[j]) or (j > 0 and t[j - 1] in (".", "->", "::")):
            continue
        k, members = j, 0
        while True:
            if k + 1 <= hi and t[k + 1] == "(" and src.match.get(k + 1, hi + 1) <= hi:
                k = src.match[k + 1]
                if members or t[j - 1] not in (";", "{", "}"):
                    out.add((j, k))
            elif k + 1 <= hi and t[k + 1] == "[" and src.match.get(k + 1, hi + 1) <= hi:
                k = src.match[k + 1]
            if k + 2 <= hi and t[k + 1] in (".", "->") and re.match(r"[A-Za-z_]", t[k + 2]):
                out.add((j, k))
                k += 2
                members += 1
                continue
            break
        if members:
            out.add((j, k))
    return sorted(out)


def stmt_scan_ranges(src, s):
    """Token ranges of a statement that belong to it (not to nested statements)."""
    if s["kind"] == "simple" or s["kind"] == "jump":
        return [(s["start"], s["end"])]
    if s["kind"] in ("if", "loop") and "cond" in s:
        return [s["cond"]]
    return []


def probe_types(text, ext, flags, cc, workdir, focus=None):
    """{(function index, expression text): type} for the candidate expressions of every statement. A probe
    declaration `struct __mqN { int z; } __mvN = (expr);` before the statement makes armcc name the type
    it cannot convert. armcc stops after 30 errors (bypassed initialisations in a switch count too), so
    each distinct expression is probed once, in small batches."""
    src = Src(text, focus)
    probes, where = [], []
    for b, i, s in src.stmts():
        for lo, hi in stmt_scan_ranges(src, s):
            for a, z in chains(src, lo, hi):
                f = src.func_of(a)
                if f is not None and (f, src.span(a, z)) not in probes:
                    probes.append((f, src.span(a, z)))
                    where.append(s["start"])
    exe = os.path.join(ROOT, "tools", "armcc", *cc.split("/"), "bin", "armcc.exe")
    fast = os.path.join(ROOT, "tools", "armcc", "4.1", "b1049ns", "bin", "armcc.exe")
    if cc == "4.1/b1049" and os.name == "nt" and os.path.exists(fast):
        exe = fast
    path = os.path.join(workdir, "probe" + ext)
    out_types = {}
    for batch in range(0, len(probes), 12):
        ins = {}
        for n in range(batch, min(batch + 12, len(probes))):
            ins.setdefault(src.S[where[n]], []).append(
                "\nstruct __mq%d { int z; } __mv%d = (%s);\n" % (n, n, probes[n][1]))
        open(path, "w").write(edit_tokens(src, [(p, p, "".join(v)) for p, v in ins.items()]))
        args = [exe, "-c", "--cpp" if ext in (".cpp", ".cc") else "--c99"] + flags.split() + \
            ["-I", os.path.join(ROOT, "shared", "include"), "-o", os.path.join(workdir, "probe.o"), path]
        if os.name != "nt":
            args = ["wine"] + args
        r = subprocess.run(args, capture_output=True, text=True)
        for m in re.finditer(r'(?:a value of type|conversion from|convert from) "(.+?)"'
                             r'(?: cannot be used to initialize an entity of type "struct __mq| to "__mq)(\d+)"',
                             r.stdout + r.stderr):
            ty, n = m.group(1), int(m.group(2))
            if not re.search(r"[()\[]|<unnamed>|__mq|^void$", ty):
                out_types[probes[n]] = ty
    for f in (path, os.path.join(workdir, "probe.o")):
        if os.path.exists(f):
            os.remove(f)
    return out_types


def ident_unused(text, base):
    k = 0
    while re.search(r"\b%s%d\b" % (base, k), text):
        k += 1
    return "%s%d" % (base, k)


def find_seq(t, seq, lo, hi):
    n = len(seq)
    return [j for j in range(lo, hi - n + 2) if t[j:j + n] == seq]


def edit_tokens(src, edits):
    """Apply non-overlapping edits (first raw token, last raw token + 1, replacement) to the source text."""
    out, last = [], 0
    for a, b, rep in sorted(edits, key=lambda e: (e[0], e[1])):
        if a < last:
            return None
        out.append("".join(x for _, x in src.toks[last:a]))
        out.append(rep)
        last = b
    out.append("".join(x for _, x in src.toks[last:]))
    return "".join(out)


def m_temp(src, rng, types):
    cands = []
    for b, i, s in src.stmts():
        for lo, hi in stmt_scan_ranges(src, s):
            for a, z in chains(src, lo, hi):
                ty = types.get((src.func_of(a), src.span(a, z)))
                if ty:
                    cands.append((b, i, a, z, ty))
    if not cands:
        return None
    b, i, a, z, ty = rng.choice(cands)
    t, s = src.t, b[i]
    seq = t[a:z + 1]
    ptr_mode = t[z + 1] == "."  # a struct value: go through a pointer
    if ptr_mode and t[z] == ")":
        return None  # no address of a call result
    edits = []
    for j in find_seq(t, seq, s["start"], b[-1]["end"]):
        e = j + len(seq) - 1
        before, after = t[j - 1], t[e + 1]
        if before in (".", "->", "::") or after == "(":
            continue  # inside a longer chain, or a call through the chain's last member
        if ptr_mode:
            if after == ".":
                edits.append((src.S[j], src.S[e + 1] + 1, None, "->"))
            elif before == "&":
                edits.append((src.S[j - 1], src.S[e] + 1, None, ""))
            else:
                edits.append((src.S[j], src.S[e] + 1, "(*", ")"))
        else:
            if after in ASSIGN or after in ("++", "--") or before in ("++", "--", "&"):
                break  # written or addressed: the value may change from here on
            edits.append((src.S[j], src.S[e] + 1, "", ""))
        if rng.random() < 0.25:
            break  # sometimes only the first uses
    if not edits:
        return None
    name = ident_unused(src.text, "t")
    expr = src.span(a, z)
    decl = ("%s* %s = &%s;" if ptr_mode else "%s %s = %s;") % (ty, name, expr)
    ins = src.S[s["start"]]
    return edit_tokens(src, [(x0, x1, (pre or "") + name + post) for x0, x1, pre, post in edits] +
                       [(ins, ins, decl + "\n" + src.indent(s["start"]))])


DECL_RE = re.compile(r"^(?:const\s+)?[A-Za-z_][\w:<>]*(?:\s*[*&]\s*|\s+)+([A-Za-z_]\w*)\s*=\s*(.+);$", re.S)


def inline_candidates(src):
    """(declaration statement, its single later use, initialiser) for every local used exactly once."""
    t = src.t
    cands = []
    for b, i, s in src.stmts():
        if s["kind"] != "simple":
            continue
        txt = src.span(s["start"], s["end"])
        m = DECL_RE.match(txt)
        if not m or t[s["start"]] in ("return",) or "," in t[s["start"]:s["end"]]:
            continue
        name = m.group(1)
        f = src.func_of(s["start"])
        o, c = src.bodies[f]
        uses = [j for j in range(o, c) if t[j] == name and t[j - 1] not in (".", "->", "::")]
        later = [j for j in uses if j > s["end"]]
        if len(uses) != 2 or len(later) != 1:
            continue
        u = later[0]
        if (u + 1 < len(t) and (t[u + 1] in ASSIGN or t[u + 1] in ("++", "--"))) or t[u - 1] in ("&", "++", "--"):
            continue
        cands.append((s, u, m.group(2).strip()))
    return cands


def apply_inline(src, cand):
    s, u, init = cand
    rep = init if re.fullmatch(r"[\w.\->\[\]]+", init) else "(" + init + ")"
    pre = "".join(x for _, x in src.toks[:src.S[s["start"]]]).rstrip(" \t")
    mid = "".join(x for _, x in src.toks[src.S[s["end"]] + 1:src.S[u]])
    post = "".join(x for _, x in src.toks[src.S[u] + 1:])
    if mid.startswith("\r\n"):
        mid = mid[2:]
    elif mid.startswith("\n"):
        mid = mid[1:]
    return pre + mid + rep + post


def m_inline(src, rng):
    cands = inline_candidates(src)
    return apply_inline(src, rng.choice(cands)) if cands else None


def forbidden(text):
    """The AGENTS.md forbidden construct a source uses, or None: campaign.FORBID's text patterns
    (weak, asm, volatile, perm_t, no-op masks, ...) plus if/else arms that are the same code."""
    import campaign  # noqa: E402
    m = campaign.FORBID.search(text)
    if m:
        return m.group(0)
    try:
        src = Src(text)
    except Exception:
        return None
    norm = lambda st: " ".join(src.span(st["start"], st["end"]).split())
    for _, _, st in src.stmts():
        if st["kind"] == "if" and "els" in st and norm(st["then"]) == norm(st["els"]):
            return "if/else arms are identical"
    return None


def simplify(text, start_text, flags, focus, run):
    """After a MATCH: inline every single-use temp the search introduced (t<N>, absent from the start)
    whose removal keeps the match, so the registered source carries no copies the bytes do not need."""
    checks = 0
    while True:
        src = Src(text, focus)
        for cand in inline_candidates(src):
            name = DECL_RE.match(src.span(cand[0]["start"], cand[0]["end"])).group(1)
            if not re.fullmatch(r"t\d+", name) or re.search(r"\b%s\b" % name, start_text):
                continue
            new = apply_inline(src, cand)
            rec = run(new, flags)
            checks += 1
            if rec.get("match") and rec.get("identity_bad") == 0:
                text = new
                break
        else:
            return text, checks


def m_helper(src, rng):
    t = src.t
    cands = []
    for g in HELPERS:
        for j, w in enumerate(t):
            if w in g and (w in TYPE_HELPERS or (j > 0 and t[j - 1] in (".", "->") and t[j + 1] == "(")):
                cands.append((j, g))
    if not cands:
        return None
    j, g = rng.choice(cands)
    new = rng.choice([x for x in g if x != t[j]])
    if t[j] in TYPE_HELPERS:  # a type: rename every use
        return re.sub(r"\b%s\b" % re.escape(t[j]), new, src.text)
    return src.splice(j, j, new)


DECLARES = re.compile(r"[\w*&]\s+[*&]*\w")  # `T x` / `T* x`: a declaration, not an lvalue
INT_ALT = {"int": ("unsigned", "u32", "s32"), "unsigned": ("int", "s32"), "s32": ("u32", "int"),
           "u32": ("s32", "int"), "u8": ("s8", "u32", "int"), "s8": ("u8", "int"), "u16": ("s16", "u32", "int"),
           "s16": ("u16", "int")}


def m_retype(src, rng):
    """An integer type word in a focus body or its parameter list -> the other signedness or a full word
    (byte-identical code needs the original's types; signedness picks between ldrb/ldrsb, lsr/asr, ...)."""
    t = src.t
    known = {w for w in INT_ALT if w in ("int", "unsigned") or re.search(r"\b%s\b" % w, src.text)}
    cands = []
    for n in src.active:
        o, c = src.bodies[n]
        p = o - 1 if t[o - 1] == ")" else o - 2
        lo = src.match.get(p, o)
        cands += [j for j in range(lo, c) if t[j] in INT_ALT and t[j - 1] not in ("unsigned", "signed")
                  and t[j + 1] not in ("int", "char", "short", "long", "*")]  # pointee: scales arithmetic
    if not cands:
        return None
    j = rng.choice(cands)
    alts = [w for w in INT_ALT[t[j]] if w in known]
    return src.splice(j, j, rng.choice(alts)) if alts else None


ASSIGN_STMT = re.compile(r"^([^=;]+?)\s*=\s*([^=;]+?)\s*;$", re.S)


def m_chain(src, rng):
    """`a = K; b = K;` <-> `a = b = K;` for a literal or plain name K: one register or two."""
    cands = []
    for b, i, s in src.stmts():
        if s["kind"] != "simple":
            continue
        txt = src.span(s["start"], s["end"])
        m = re.match(r"^([^=;]+?)\s*=\s*([^=;]+?)\s*=\s*([\w.]+)\s*;$", txt)
        if m and not re.search(r"[!<>+\-*/%&|^]$", m.group(1)) and not DECLARES.search(m.group(2)):
            cands.append(("split", s, None, m))
        m1 = ASSIGN_STMT.match(txt)
        if m1 and i + 1 < len(b) and b[i + 1]["kind"] == "simple" and re.fullmatch(r"[\w.]+", m1.group(2)):
            m2 = ASSIGN_STMT.match(src.span(b[i + 1]["start"], b[i + 1]["end"]))
            plain = lambda lhs: not re.search(r"[!<>+\-*/%&|^]$", lhs) and not DECLARES.search(lhs)
            if m2 and m2.group(2) == m1.group(2) and plain(m1.group(1)) and plain(m2.group(1)):
                cands.append(("merge", s, b[i + 1], (m1, m2)))
    if not cands:
        return None
    kind, s, s2, m = rng.choice(cands)
    if kind == "split":
        ind = src.indent(s["start"])
        return src.splice(s["start"], s["end"], "%s = %s;\n%s%s = %s;" % (
            m.group(2), m.group(3), ind, m.group(1), m.group(3)))
    m1, m2 = m
    return src.splice(s["start"], s2["end"], "%s = %s = %s;" % (m2.group(1), m1.group(1), m1.group(2)))


def m_nest(src, rng):
    """`if (a && b) S` (no else) -> `if (a) { if (b) S }`: another block layout for the same test."""
    t = src.t
    cands = []
    for _, _, s in src.stmts():
        if s["kind"] != "if" or "els" in s:
            continue
        a, c = s["cond"]
        depth, ands = 0, []
        for k in range(a + 1, c):
            if t[k] in ("(", "["):
                depth += 1
            elif t[k] in (")", "]"):
                depth -= 1
            elif depth == 0 and t[k] in ("||", "?"):
                ands = []
                break
            elif depth == 0 and t[k] == "&&":
                ands.append(k)
        if ands:
            cands.append((s, a, c, ands[0]))
    if not cands:
        return None
    s, a, c, k = rng.choice(cands)
    th = s["then"]
    return src.splice(s["start"], s["end"], "if (%s) { if (%s) %s }" % (
        src.span(a + 1, k - 1), src.span(k + 1, c - 1), src.span(th["start"], th["end"])))


TEXT_MUTATIONS = [("swap", m_swap, 5), ("commute", m_commute, 3), ("flip", m_flip, 1), ("inline", m_inline, 1),
                  ("helper", m_helper, 1), ("retype", m_retype, 2), ("chain", m_chain, 1), ("nest", m_nest, 1)]


def mutate(text, flags, rng, types, flag_pool, n, focus=None):
    """Apply n random rewrites; returns (text, flags, [names]) or None."""
    names = []
    for _ in range(n):
        r = rng.random()
        if r < 0.06 and len(flag_pool) > 1:
            flags = rng.choice([f for f in flag_pool if f != flags])
            names.append("flags")
            continue
        try:
            src = Src(text, focus)
        except Exception:
            return None
        if r < 0.30 and types:
            new, name = m_temp(src, rng, types), "temp"
        else:
            tot = sum(w for _, _, w in TEXT_MUTATIONS)
            x, acc = rng.random() * tot, 0
            for name, fn_, w in TEXT_MUTATIONS:
                acc += w
                if x < acc:
                    new = fn_(src, rng)
                    break
        if new is None or new == text:
            continue
        text = new
        names.append(name)
    return (text, flags, names) if names else None


# ------------------------------------------------------------------ search

def key(rec):
    if rec.get("err"):
        return (2, 10 ** 6, 10 ** 6, 0)
    if rec["match"]:
        return (0, 0, 0, -rec["words"])
    return (1, rec["op"], rec["reg"] + rec["moved"], -rec["words"])


def brief(rec):
    if rec.get("err"):
        return {"err": rec["err"]}
    return {k: rec.get(k) for k in ("match", "op", "reg", "moved", "words", "total", "identity_bad")}


def start_source(addr, src, flags):
    if src:
        return src, flags or structscore.DEFAULT_FLAGS, structscore.DEFAULT_CC
    status = json.load(open(os.path.join(ROOT, "functions.json")))
    key_ = "%08X" % addr
    cands = []
    for d in (structscore.refine_sources(status), structscore.agent_sources(status), structscore.wip_sources(status)):
        if key_ in d:
            cands.append(d[key_])
    if not cands:
        sys.exit("no source known for %s: pass --src" % key_)
    scores = structscore.score_many(cands)
    it = min(zip(cands, scores), key=lambda x: structscore.rank(x[1]))[0]
    return it["path"], flags or it["flags"], it["cc"]


def search(addr, src, flags, a, fanout=None):
    import refine  # noqa: E402  (flag_variants)
    import worklist  # noqa: E402  (rebase_includes)
    key_ = "%08X" % addr
    wd = os.path.join(OUT, key_)
    os.makedirs(wd, exist_ok=True)  # variants live beside start/best/match: one include base for all
    src, flags, cc = start_source(addr, src, flags)
    ext = os.path.splitext(src)[1] or ".c"
    text0 = worklist.rebase_includes(open(src, errors="replace").read(), wd, os.path.dirname(os.path.abspath(src)))
    if a.dehack:
        text0 = BARRIER_RE.sub("", text0)
    start_path = os.path.join(wd, "start" + ext)
    open(start_path, "w").write(text0)
    rng = random.Random(a.seed)
    flag_pool = [flags] if a.no_flags else refine.flag_variants(flags)
    t0 = time.time()
    start = structscore.check(addr, start_path, flags, cc)
    yours = re.search(r"yours '([^']+)'", start.pop("out", ""))
    focus = focus_names(text0, yours.group(1)) if yours else None
    types = probe_types(text0, ext, flags, cc, wd, focus)
    print("%s: start %s (%s), mutating %s, %d typed sub-expressions probed in %.1fs" % (
        key_, os.path.relpath(src, ROOT), " ".join(flags.split()[-3:-1]), ", ".join(sorted(focus)) if focus else
        "every function", len(types), time.time() - t0), flush=True)

    def run(text, fl):
        h = hashlib.sha1(text.encode() + fl.encode()).hexdigest()[:12]
        path = os.path.join(wd, "v_%s%s" % (h, ext))
        open(path, "w").write(text)
        rec = structscore.check(addr, path, fl, cc)
        rec.pop("out", None)
        try:
            os.remove(path)
        except OSError:
            pass
        return rec

    print("  start: %s" % brief(start), flush=True)

    best = cur = (key(start), text0, flags, [])
    open(os.path.join(wd, "best" + ext), "w").write(text0)  # a previous run's best must not survive this run
    elite = [best]
    seen = {hashlib.sha1(text0.encode() + flags.encode()).digest()}
    checks, stale, restarts, errors = 1, 0, 0, 0
    log = open(os.path.join(wd, "score.jsonl"), "a")
    log.write(json.dumps({"t": 0, "checks": 1, "best": brief(start), "flags": flags, "muts": []}) + "\n")
    deadline = t0 + a.minutes * 60 if a.minutes else None
    done_rec = start if start.get("match") else None
    inflight = {}
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        while done_rec is None:
            out_of_time = deadline and time.time() > deadline
            while not out_of_time and len(inflight) < a.jobs and checks + len(inflight) < a.budget:
                parent = cur if rng.random() < 0.8 else rng.choice(elite)
                for _ in range(30):
                    v = mutate(parent[1], parent[2], rng, types, flag_pool, rng.choice((1, 1, 1, 2, 2, 3)), focus)
                    if v is None:
                        continue
                    h = hashlib.sha1(v[0].encode() + v[1].encode()).digest()
                    if h in seen:
                        continue
                    seen.add(h)
                    inflight[ex.submit(run, v[0], v[1])] = (v[0], v[1], parent[3] + v[2])
                    break
                else:
                    break
            if not inflight:
                break
            fin, _ = wait(list(inflight), return_when=FIRST_COMPLETED)
            for fut in fin:
                text, fl, muts = inflight.pop(fut)
                rec = fut.result()
                checks += 1
                errors += bool(rec.get("err"))
                k = key(rec)
                state = (k, text, fl, muts[-12:])
                if k < best[0]:
                    best, stale = state, 0
                    open(os.path.join(wd, "best" + ext), "w").write(text)
                    log.write(json.dumps({"t": round(time.time() - t0, 1), "checks": checks, "best": brief(rec),
                                          "flags": fl, "muts": muts[-12:]}) + "\n")
                    log.flush()
                    print("  [%5d] best %s  via %s" % (checks, brief(rec), ",".join(muts[-4:])), flush=True)
                    if rec.get("match"):
                        done_rec = rec
                else:
                    stale += 1
                if k <= cur[0]:
                    cur = state
                if k[0] < 2 and all(k != e[0] or text != e[1] for e in elite):
                    elite = sorted(elite + [state], key=lambda e: e[0])[:8]
            if stale > a.patience:
                cur = rng.choice(elite + [(key(start), text0, flags, [])])
                stale, restarts = 0, restarts + 1
            if done_rec is None and (checks >= a.budget or (deadline and time.time() > deadline)) and not inflight:
                break
        for f in inflight:
            f.cancel()
    log.close()

    bk, btext, bflags, bmuts = best
    status = "EXHAUSTED"
    res = dict(addr=key_, start_src=os.path.relpath(src, ROOT), checks=checks, errors=errors, restarts=restarts,
               seconds=round(time.time() - t0), start=brief(start), flags=bflags, muts=bmuts, fanout=fanout,
               registered=False, dehack=bool(a.dehack))
    final = structscore.check(addr, os.path.join(wd, "best" + ext), bflags, cc)
    final.pop("out", None)
    res["best"] = brief(final)
    if final.get("match"):
        if final.get("identity_bad"):
            status = "IDENTITY"
        else:
            status = "MATCH"
            btext, res["simplify_checks"] = simplify(btext, text0, bflags, focus, run)
            mpath = os.path.join(wd, "match" + ext)
            open(mpath, "w").write(btext)
            res["match_path"] = os.path.relpath(mpath, ROOT)
            bad = forbidden(btext)
            if bad:
                res["forbidden"] = bad
            elif a.register:
                r = subprocess.run([PY, os.path.join(ROOT, "tools", "worklist.py"), "register", "0x" + key_,
                                    "--src", mpath, "--flags=" + bflags], capture_output=True, text=True, cwd=ROOT)
                res["registered"] = "-> honest" in r.stdout
                res["register_out"] = r.stdout.strip().splitlines()[-3:]
    res["status"] = status
    json.dump(res, open(os.path.join(wd, "result.json"), "w"), indent=1)
    print("%s: %s after %d checks (%d restarts, %ds): start %s -> best %s%s" % (
        key_, status, checks, restarts, res["seconds"], brief(start), res["best"],
        "  registered" if res["registered"] else ""), flush=True)
    return res


def tidy(a):
    """Re-simplify the sources of earlier MATCH runs: inline every single-use t<N> temp the search
    introduced that the bytes do not need, and re-register through worklist.py register."""
    import glob
    for p in sorted(glob.glob(os.path.join(OUT, "*", "result.json"))):
        r = json.load(open(p))
        if r.get("status") != "MATCH" or not r.get("match_path"):
            continue
        wd = os.path.dirname(p)
        key_ = r["addr"]
        mpath = os.path.join(ROOT, r["match_path"])
        starts = [f for f in os.listdir(wd) if f.startswith("start.")]
        if not starts:
            continue
        ext = os.path.splitext(starts[0])[1]
        text, start_text = open(mpath).read(), open(os.path.join(wd, starts[0])).read()
        vpath = os.path.join(wd, "v_tidy" + ext)

        def run(t, fl):
            open(vpath, "w").write(t)
            return structscore.check(int(key_, 16), vpath, fl, structscore.DEFAULT_CC)

        new, checks = simplify(text, start_text, r["flags"], None, run)
        r["simplify_checks"] = r.get("simplify_checks", 0) + checks
        if new != text:
            open(mpath, "w").write(new)
            if a.register:
                res = subprocess.run([PY, os.path.join(ROOT, "tools", "worklist.py"), "register", "0x" + key_,
                                      "--src", mpath, "--flags=" + r["flags"]],
                                     capture_output=True, text=True, cwd=ROOT)
                r["registered"] = "-> honest" in res.stdout
            print("%s: simplified (%d checks), registered %s" % (key_, checks, r.get("registered")), flush=True)
        else:
            print("%s: nothing to simplify (%d checks)" % (key_, checks), flush=True)
        if os.path.exists(vpath):
            os.remove(vpath)
        json.dump(r, open(p, "w"), indent=1)


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("target", help="function address; 'queue' for logs/campaign/search_queue.jsonl; 'barriers' "
                                   "for the __schedule_barrier hacks in " + os.path.relpath(BARRIERS, ROOT) +
                                   "; 'tidy' re-simplifies the sources of earlier MATCH runs")
    ap.add_argument("--src")
    ap.add_argument("--flags")
    ap.add_argument("--budget", type=int, default=5000, help="checks per function")
    ap.add_argument("--minutes", type=float, default=0, help="wall-clock limit per function (0: none)")
    ap.add_argument("--jobs", type=int, default=16)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--patience", type=int, default=300, help="checks without a new best before a restart")
    ap.add_argument("--no-flags", action="store_true", help="keep the start flags")
    ap.add_argument("--register", action="store_true", help="register a MATCH through worklist.py register")
    ap.add_argument("--limit", type=int, default=0, help="queue: at most N functions")
    ap.add_argument("--again", action="store_true", help="queue/barriers: also functions with a result.json")
    ap.add_argument("--dehack", action="store_true", help="delete __schedule_barrier(); from the start source")
    a = ap.parse_args()
    if a.target == "tidy":
        tidy(a)
        return
    if a.target not in ("queue", "barriers"):
        search(int(a.target, 16), a.src, a.flags, a)
        return
    if a.target == "queue":
        jobs = [(e["addr"], os.path.join(ROOT, e["path"]), e["flags"], e["fanout"])
                for e in (json.loads(l) for l in open(structscore.QUEUE) if l.strip())]
    else:  # the hack's own source, barrier deleted, at its recorded flags
        status = json.load(open(os.path.join(ROOT, "functions.json")))
        a.dehack = True
        jobs = [(k, os.path.join(ROOT, status[k]["path"]), status[k]["flags"], None)
                for k in json.load(open(BARRIERS)) if status.get(k, {}).get("status") == "hack"]
    n = 0
    for addr, path, flags, fanout in jobs:
        if not a.again and os.path.exists(os.path.join(OUT, addr, "result.json")):
            continue
        search(int(addr, 16), path, flags, a, fanout=fanout)
        n += 1
        if a.limit and n >= a.limit:
            break


if __name__ == "__main__":
    main()
