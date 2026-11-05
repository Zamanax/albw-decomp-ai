#!/usr/bin/env python3
"""Shared-header migration harness: replace file-local type definitions with a shared header.

  python tools/headermigrate.py <Type[,Type2...]> <header.h> [--apply] [--jobs 16] [--limit N]
         [--paths a,b] [--lang cpp|c|both] [--template T] [--rename REGEX=REPL ...] [--log NAME]

For every matched source (at least one honest entry) that defines the first type at file or
namespace scope (`struct|class Type [: bases] { ... };`, optionally `template<...>`-prefixed), build
a candidate in which the definitions of ALL listed types are removed and `#include "<header.h>"`
(resolved through shared/include) is inserted where the first one was, or, if it sat inside
`namespace X { }`, just before the outermost enclosing namespace. Then compile-check EVERY
functions.json entry that points at the file, with its recorded flags. A file migrates only if
all of them still print RESULT: MATCH and IDENTITY ... 0 MISMATCH; otherwise it is left alone.

--template T: the header defines `template<class O> struct T`; the owner class is read from the
removed definition's `X* mOwner;` and the file gets `typedef T<X> Type;`.
--rename: regex rewrites applied to the rest of the file (member-name differences).

Without --apply nothing in src/ changes: candidates are written next to the source as
__hm<pid>_<file> (unique per run, so several dry runs can proceed in parallel) and removed.
Per-file outcomes go to logs/headermigrate/<log>.jsonl:
  ok | compile_error | nomatch (with words) | identity | no_definition
The share of `ok` measures how many independently matched functions agree with the header's
helper forms; the failures are the evidence for which forms the header still gets wrong.
Apply runs must not overlap (two runs could rewrite the same file); dry runs may.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
RESULT = re.compile(r"RESULT: (NO MATCH|MATCH)\s+(\d+)/(\d+) words")
IDENTITY = re.compile(r"IDENTITY: (\d+) verified, (\d+) unverifiable, (\d+) MISMATCH")
OWNER_FIELD = re.compile(r"\b(\w+)\s*\*\s*mOwner\s*;")
LANG_EXT = {"cpp": (".cpp",), "c": (".c",), "both": (".cpp", ".c")}


def blank_noise(text):
    """Comments and string/char literals replaced by spaces (same length), for brace scanning."""
    return re.sub(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'",
                  lambda m: " " * len(m.group(0)), text, flags=re.S)


def scopes(clean, pos):
    """Enclosing brace scopes at pos: list of (kind, start) with kind 'ns' or 'other', outermost first.

    For a namespace, start is the index of its `namespace` keyword.
    """
    stack = []
    for m in re.finditer(r"[{}]", clean[:pos]):
        if m.group(0) == "{":
            head = clean[:m.start()]
            k = re.search(r"\bnamespace(\s+\w+)?\s*$", head)
            stack.append(("ns", k.start()) if k else ("other", m.start()))
        elif stack:
            stack.pop()
    return stack


def find_definition(text, name, clean=None):
    """(start, end, insert_at) of a namespace/file-scope definition of `name`, or None.

    start includes a `template<...>` prefix; end includes the closing `;`. insert_at is where an
    #include can replace it: the start itself at file scope, else the outermost namespace keyword.
    A definition followed by a declarator (`struct X {...} x;`) is not removable and is skipped.
    """
    clean = blank_noise(text) if clean is None else clean
    for m in re.finditer(r"\b(?:struct|class)\s+%s\s*(?::[^{;()]*)?\{" % re.escape(name), clean):
        sc = scopes(clean, m.start())
        if any(kind != "ns" for kind, _ in sc):
            continue
        start = m.start()
        t = re.search(r"\btemplate\s*<[^;{}]*>\s*$", clean[:start])
        if t:
            start = t.start()
        depth, end = 0, None
        for j in range(clean.index("{", m.start()), len(clean)):
            if clean[j] == "{":
                depth += 1
            elif clean[j] == "}":
                depth -= 1
                if depth == 0:
                    end = j + 1
                    break
        if end is None:
            return None
        k = re.match(r"\s*;", clean[end:])
        if not k:
            continue
        return start, end + k.end(), (sc[0][1] if sc else start)
    return None


def candidate(text, names, header, template=None, renames=()):
    """The source with the local definitions of `names` replaced by the shared header, or None."""
    clean = blank_noise(text)
    spans = []
    for i, name in enumerate(names):
        d = find_definition(text, name, clean)
        if d is None:
            if i == 0:
                return None
            continue
        spans.append((name, d))
    first_name, (s0, e0, ins) = spans[0]
    inc = '\n#include "%s"\n' % header
    if template:
        owner = OWNER_FIELD.search(text[s0:e0])
        if not owner:
            return None
        inc += "typedef %s<%s> %s;\n" % (template, owner.group(1), first_name)
    # cut from the back so earlier offsets stay valid, then insert the include
    cuts = sorted(((s, e) for _, (s, e, _) in spans), reverse=True)
    out = text
    for s, e in cuts:
        out = out[:s] + out[e:]
    removed_before = sum(e - s for s, e in cuts if e <= ins)
    at = ins - removed_before
    head, rest = out[:at], out[at:]
    for pat, sub in renames:
        rest = re.sub(pat, sub, rest)
    return head + inc + rest


def check(path, key, flags):
    out = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", path, "0x" + key,
                          "flags", flags], capture_output=True, text=True, cwd=ROOT, timeout=300).stdout
    if "COMPILE ERROR" in out or "Error:" in out:
        err = next((l.strip() for l in out.splitlines() if "Error:" in l), "compile error")
        return "compile_error", err[:200]
    r, i = RESULT.search(out), IDENTITY.search(out)
    if not r:
        return "compile_error", (out.strip().splitlines() or ["no output"])[-1][:200]
    if r.group(1) != "MATCH":
        return "nomatch", "%s/%s words" % (r.group(2), r.group(3))
    if not i or int(i.group(3)):
        return "identity", (i.group(0) if i else "no IDENTITY line")
    return "ok", "%s/%s" % (r.group(2), r.group(3))


def try_file(path, entries, names, header, apply, template=None, renames=()):
    full = os.path.join(ROOT, path)
    text = open(full, encoding="utf-8", errors="replace").read()
    new = candidate(text, names, header, template, renames)
    if new is None:
        return dict(path=path, outcome="no_definition")
    d, f = os.path.split(full)
    tmp = os.path.join(d, "__hm%d_%s" % (os.getpid(), f))
    open(tmp, "w", encoding="utf-8").write(new)
    try:
        for key, ent in entries:
            outcome, detail = check(tmp, key, ent.get("flags") or DEFAULT_FLAGS)
            if outcome != "ok":
                return dict(path=path, outcome=outcome, addr=key, detail=detail)
    finally:
        os.remove(tmp)
    if apply:
        open(full, "w", encoding="utf-8").write(new)
    return dict(path=path, outcome="ok", entries=[k for k, _ in entries])


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("types", help="comma-separated; the first one selects the files")
    ap.add_argument("header")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--jobs", type=int, default=16)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--paths", help="comma-separated repo paths to restrict to")
    ap.add_argument("--lang", choices=sorted(LANG_EXT), default="cpp")
    ap.add_argument("--template", help="header defines template<class T> struct TEMPLATE; owner from mOwner")
    ap.add_argument("--rename", action="append", default=[], metavar="REGEX=REPL",
                    help="rewrite member names in the rest of the file (repeatable; use --rename=...)")
    ap.add_argument("--log", help="log name under logs/headermigrate (default: the first type)")
    a = ap.parse_args()
    names = a.types.split(",")
    renames = [tuple(r.split("=", 1)) for r in a.rename]

    data = json.load(open(os.path.join(ROOT, "functions.json")))
    by_path = {}
    for key, ent in sorted(data.items()):
        if ent.get("status") in ("honest", "hack") and ent.get("path"):
            by_path.setdefault(ent["path"], []).append((key, ent))
    pat = re.compile(r"\b(?:struct|class)\s+%s\s*(?::[^{;()]*)?\{" % re.escape(names[0]))
    paths = sorted(p for p, es in by_path.items()
                   if p.endswith(LANG_EXT[a.lang]) and any(e["status"] == "honest" for _, e in es)
                   and os.path.exists(os.path.join(ROOT, p))
                   and pat.search(open(os.path.join(ROOT, p), encoding="utf-8", errors="replace").read()))
    if a.paths:
        keep = set(a.paths.split(","))
        paths = [p for p in paths if p in keep]
    if a.limit:
        paths = paths[:a.limit]

    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda p: try_file(p, by_path[p], names, a.header, a.apply, a.template, renames),
                          paths))

    os.makedirs(os.path.join(ROOT, "logs", "headermigrate"), exist_ok=True)
    with open(os.path.join(ROOT, "logs", "headermigrate", (a.log or names[0]) + ".jsonl"), "w") as fh:
        for r in res:
            fh.write(json.dumps(r) + "\n")
    counts = {}
    for r in res:
        counts[r["outcome"]] = counts.get(r["outcome"], 0) + 1
    print("%s -> %s: %d files %s%s" % (a.types, a.header, len(res), json.dumps(counts, sort_keys=True),
                                       " (applied)" if a.apply else ""))


if __name__ == "__main__":
    main()
