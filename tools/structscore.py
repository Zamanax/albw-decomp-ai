#!/usr/bin/env python
"""Structural scores (fn.py check's STRUCTURE line) for many sources, cached, and the impact census.

  uv run python tools/structscore.py census [--sample 100] [--jobs 16] [--seed 1]

census prints how many functions each step of the register/order search reaches:
  step 1  spot-check: N random honest entries must all be OP=0 REG=0 MOVED=0;
          every unmatched function with a best source (refine's logs/refine/<A>/state.json and
          the agents' logs/manual/*/REPORT.json), bucketed by its best structure, with the
          number of functions the same shape families reach (famclone clones a match onto them);
  step 2  logs/campaign/search_queue.jsonl (written by campaign.py next): queued functions,
          family reach, and how many the paid plan would have taken;
  step 3  logs/mutate/<A>/result.json (written by mutate.py): searched / matched / best reached.

Scores are cached in logs/structure/cache.jsonl, keyed by address, cc, flags, source text and
SCORE_VERSION (bump it when fn.py's STRUCTURE logic changes).
"""
import argparse
import collections
import hashlib
import json
import os
import random
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_CC = "4.1/b1049"
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
SCORE_VERSION = 10   # 10: the key includes the file extension (a .cpp and a .c with the same text compile differently)
SDIR = os.path.join(ROOT, "logs", "structure")
CACHE = os.path.join(SDIR, "cache.jsonl")
CACHE_DIR = os.path.join(SDIR, "cache")
QUEUE = os.path.join(ROOT, "logs", "campaign", "search_queue.jsonl")
MUTATE = os.path.join(ROOT, "logs", "mutate")

RESULT_RE = re.compile(r"RESULT: (MATCH|NO MATCH)\s+(\d+)/(\d+) words")
IDENTITY_RE = re.compile(r"IDENTITY: (\d+) verified, (\d+) unverifiable, (\d+) MISMATCH")
STRUCTURE_RE = re.compile(r"STRUCTURE: OP=(\d+) REG=(\d+) MOVED=(\d+) aligned (\d+)/(\d+)")
OPS_RE = re.compile(r"STRUCTURE OPS: (.*)")
POOL_RE = re.compile(r"pool (\d+)/(\d+)")
ORDER_ONLY_OP = re.compile(r"^[-+](?:mov R, R|b(?:eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le) LOCAL)$")


def parse(out):
    """dict(match, words, total, identity_bad, op, reg, moved, aligned, n, ops) from fn.py check output;
    err set when there is no RESULT/STRUCTURE line."""
    r, s = RESULT_RE.search(out), STRUCTURE_RE.search(out)
    if not r or not s:
        lines = out.strip().splitlines() or ["no output"]
        return dict(err=next((l for l in lines if "rror" in l), lines[-1])[:120])
    i = IDENTITY_RE.search(out)
    o = OPS_RE.search(out)
    p = POOL_RE.search(out)
    return dict(err="", match=r.group(1) == "MATCH", words=int(r.group(2)), total=int(r.group(3)),
                identity_bad=int(i.group(3)) if i else None, pool=(int(p.group(1)), int(p.group(2))) if p else None,
                op=int(s.group(1)), reg=int(s.group(2)), moved=int(s.group(3)),
                aligned=int(s.group(4)), n=int(s.group(5)),
                ops=o.group(1).split(" | ") if o else [])


def order_only(rec):
    """OP small and every OP an allocation/order artefact: a register copy (mov R, R) present on one side
    only, or a local branch whose condition flipped (blocks laid out the other way round)."""
    ops = rec.get("ops", [])
    return 0 < rec["op"] <= 2 and len(ops) <= 4 and all(ORDER_ONLY_OP.match(x) for x in ops)


def check(addr, path, flags=DEFAULT_FLAGS, cc=DEFAULT_CC, timeout=300):
    """Run fn.py check once (no cache); returns parse() + out."""
    args = [sys.executable, os.path.join(ROOT, "tools", "fn.py"), "check", path, "0x%08X" % addr,
            "--cc", cc or DEFAULT_CC, "--flags", flags or DEFAULT_FLAGS]
    try:
        out = subprocess.run(args, capture_output=True, text=True, cwd=ROOT, timeout=timeout).stdout
    except subprocess.TimeoutExpired:
        return dict(err="TIMEOUT", out="")
    rec = parse(out)
    rec["out"] = out
    return rec


def _key(addr, path, flags, cc):
    try:
        text = open(path, "rb").read()
    except OSError:
        return None
    h = hashlib.sha1(b"%d|%08X|%s|%s|%s|" % (SCORE_VERSION, addr, (cc or "").encode(), (flags or "").encode(),
                                            os.path.splitext(path)[1].encode()))
    h.update(text)
    return h.hexdigest()


def _load_cache():
    """Every cache shard (one per writer process: concurrent tools never interleave a line)."""
    out = {}
    paths = [CACHE] + ([os.path.join(CACHE_DIR, f) for f in os.listdir(CACHE_DIR)] if os.path.isdir(CACHE_DIR) else [])
    for path in paths:
        if not os.path.exists(path):
            continue
        for l in open(path, errors="replace"):
            try:
                d = json.loads(l)
                out[d["key"]] = d
            except ValueError:
                pass
    return out


def score_many(items, jobs=16, progress=False):
    """items: dicts with addr (int), path, flags, cc. Returns a list of score dicts (same order); cached."""
    os.makedirs(SDIR, exist_ok=True)
    cache = _load_cache()
    keys = [_key(it["addr"], it["path"], it.get("flags"), it.get("cc")) for it in items]
    todo = [(i, it) for i, (it, k) in enumerate(zip(items, keys)) if k and k not in cache]
    res = [None] * len(items)
    for i, k in enumerate(keys):
        if k is None:
            res[i] = dict(err="missing source")
        elif k in cache:
            res[i] = cache[k]
    if todo:
        if progress:
            print("  scoring %d sources (%d cached)" % (len(todo), len(items) - len(todo)), flush=True)
        os.makedirs(CACHE_DIR, exist_ok=True)
        with ThreadPoolExecutor(max_workers=jobs) as ex, open(os.path.join(CACHE_DIR, "%d.jsonl" % os.getpid()), "a") as fh:
            futs = {ex.submit(check, it["addr"], it["path"], it.get("flags"), it.get("cc")): i for i, it in todo}
            done = 0
            for fut, i in futs.items():
                rec = fut.result()
                rec.pop("out", None)
                if rec["err"] != "TIMEOUT":
                    rec["key"] = keys[i]
                    fh.write(json.dumps(rec) + "\n")
                    fh.flush()
                res[i] = rec
                done += 1
                if progress and done % 500 == 0:
                    print("  ... %d/%d" % (done, len(todo)), flush=True)
    return res


def rank(rec):
    """Sort key: fewest OP, then REG+MOVED (errors last)."""
    if not rec or rec.get("err"):
        return (1, 10 ** 9, 10 ** 9)
    if rec["match"]:
        return (0, -1, 0)
    return (0, rec["op"], rec["reg"] + rec["moved"])


# ------------------------------------------------------------------ candidate sources

def matched(status):
    return {k for k, v in status.items() if v.get("status") in ("honest", "hack")}


def refine_sources(status):
    """addr -> source dict for refine's best of every unmatched function (wave file with its real extension)."""
    out = {}
    rdir = os.path.join(ROOT, "logs", "refine")
    done = matched(status)
    for a in os.listdir(rdir):
        p = os.path.join(rdir, a, "state.json")
        if a in done or not os.path.exists(p):
            continue
        try:
            st = json.load(open(p))
        except ValueError:
            continue
        b = st.get("best") or {}
        if not b.get("total") or b.get("err") or b.get("match"):
            continue
        path = b.get("path")
        if not path or not os.path.exists(path):
            best = os.path.join(rdir, a, "best.c")
            if not os.path.exists(best):
                continue
            path = os.path.join(SDIR, "src", a + st.get("ext", ".c"))
            os.makedirs(os.path.dirname(path), exist_ok=True)
            shutil.copyfile(best, path)
        out[a] = dict(addr=int(a, 16), path=path, flags=b.get("flags") or DEFAULT_FLAGS, cc=DEFAULT_CC,
                      origin="refine")
    return out


def agent_sources(status):
    """addr -> source dict for the agents' best (logs/manual/*/REPORT.json, not MATCH, file present).
    campaign.py next renames the REPORT.json of a re-planned target to REPORT.prev.json: read that too."""
    out = {}
    man = os.path.join(ROOT, "logs", "manual")
    done = matched(status)
    for d in os.listdir(man):
        p = os.path.join(man, d, "REPORT.json")
        if not os.path.exists(p):
            p = os.path.join(man, d, "REPORT.prev.json")
        if not os.path.exists(p):
            continue
        try:
            r = json.load(open(p))
        except ValueError:
            continue
        a = str(r.get("addr", "")).replace("0x", "").upper().zfill(8)
        f = r.get("file")
        if not re.fullmatch(r"[0-9A-F]{8}", a) or a in done or r.get("status") == "MATCH" or not f:
            continue
        path = f if os.path.isabs(f) else os.path.join(ROOT, f)
        if os.path.exists(path):
            out[a] = dict(addr=int(a, 16), path=path, flags=r.get("flags") or DEFAULT_FLAGS, cc=DEFAULT_CC,
                          origin="agent")
    return out


def wip_sources(status):
    """addr -> source dict for the tracked hand-over sources shared/wip/<tag>_<ADDR>/best.{c,cpp}."""
    out = {}
    wip = os.path.join(ROOT, "shared", "wip")
    done = matched(status)
    for d in sorted(os.listdir(wip)) if os.path.isdir(wip) else []:
        m = re.search(r"([0-9A-Fa-f]{8})$", d)
        src = [os.path.join(wip, d, f) for f in ("best.cpp", "best.c") if os.path.exists(os.path.join(wip, d, f))]
        if not m or not src or m.group(1).upper() in done:
            continue
        rp = os.path.join(wip, d, "REPORT.json")
        flags = (json.load(open(rp)).get("flags") if os.path.exists(rp) else None) or DEFAULT_FLAGS
        a = m.group(1).upper()
        out[a] = dict(addr=int(a, 16), path=src[0], flags=flags, cc=DEFAULT_CC, origin="wip")
    return out


def best_structures(status, jobs=16, progress=False):
    """addr -> (best source dict, its score, per-origin scores) over refine's, the agents' (logs/manual)
    and the hand-over (shared/wip) sources."""
    srcs = [("refine", refine_sources(status)), ("agent", agent_sources(status)), ("wip", wip_sources(status))]
    items = [(a, it) for _, d in srcs for a, it in d.items()]
    scores = score_many([it for _, it in items], jobs=jobs, progress=progress)
    best = {}
    per = collections.defaultdict(dict)
    for (a, it), sc in zip(items, scores):
        per[a][it["origin"]] = sc
        if a not in best or rank(sc) < rank(best[a][1]):
            best[a] = (it, sc)
    return {a: (it, sc, per[a]) for a, (it, sc) in best.items()}


# ------------------------------------------------------------------ census

def bucket(sc):
    if not sc or sc.get("err"):
        return "error"
    if sc["match"]:
        return "MATCH"
    if sc["op"] == 0:
        return "OP=0"
    if sc["op"] <= 2:
        return "OP 1-2"
    if sc["op"] <= 5:
        return "OP 3-5"
    return "OP >5"


BUCKETS = ("MATCH", "OP=0", "OP 1-2", "OP 3-5", "OP >5", "error")


def family_reach(addrs, fan):
    """Functions reached when one member per shape matches: sum of family sizes over distinct shapes."""
    shapes = {fan[a][0]: fan[a][1] for a in addrs if a in fan}
    return sum(shapes.values()), len(shapes)


def census(a):
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import campaign  # noqa: E402  (imports fn: needs code.bin)
    status = json.load(open(os.path.join(ROOT, "functions.json")))

    print("== step 1: structural score")
    honest = sorted(k for k, v in status.items() if v.get("status") == "honest")
    pick = random.Random(a.seed).sample(honest, min(a.sample, len(honest)))
    items = [dict(addr=int(k, 16), path=os.path.join(ROOT, status[k]["path"]), flags=status[k]["flags"],
                  cc=status[k]["cc"]) for k in pick]
    sc = score_many(items, jobs=a.jobs)
    ok = [k for k, s in zip(pick, sc) if not s.get("err") and s["match"] and s["op"] == s["reg"] == s["moved"] == 0]
    print("spot-check: %d/%d random honest entries MATCH with OP=0 REG=0 MOVED=0" % (len(ok), len(pick)))
    for k, s in zip(pick, sc):
        if k not in ok:
            print("  !! %s %s" % (k, s.get("err") or "match=%s OP=%d REG=%d MOVED=%d %s" % (
                s["match"], s["op"], s["reg"], s["moved"], " | ".join(s.get("ops", [])[:4]))))

    best = best_structures(status, jobs=a.jobs, progress=True)
    fan = campaign.shape_fanout(sorted(best))
    agent = lambda p: min((p[o] for o in ("agent", "wip") if o in p), key=rank, default=None)
    print("unmatched functions with a best source: %d (refine %d, agents %d)" % (
        len(best), sum("refine" in p for _, _, p in best.values()), sum(agent(p) is not None for _, _, p in best.values())))
    print("  %-8s %8s %8s %8s %12s" % ("bucket", "refine", "agents", "best-of", "family reach"))
    for b in BUCKETS:
        nr = sum(bucket(p.get("refine")) == b for _, _, p in best.values() if "refine" in p)
        na = sum(bucket(agent(p)) == b for _, _, p in best.values() if agent(p) is not None)
        addrs = [x for x, (_, s, _) in best.items() if bucket(s) == b]
        reach, shapes = family_reach(addrs, fan)
        print("  %-8s %8d %8d %8d %6d (%d shapes)" % (b, nr, na, len(addrs), reach, shapes))
    oo = [x for x, (_, s, _) in best.items() if bucket(s) == "OP 1-2" and order_only(s)]
    reach, shapes = family_reach(oo, fan)
    print("  OP 1-2 that are order-only (mov R, R / flipped branch): %d, family reach %d (%d shapes)"
          % (len(oo), reach, shapes))

    print("\n== step 2: routing")
    if not os.path.exists(QUEUE):
        print("no search queue yet (campaign.py next writes %s)" % os.path.relpath(QUEUE, ROOT))
    else:
        q = [json.loads(l) for l in open(QUEUE) if l.strip()]
        plan = os.path.join(ROOT, "logs", "campaign", "plan.json")
        planned = {x for t in json.load(open(plan)).get("tasks", []) for x in t["addrs"]} if os.path.exists(plan) else set()
        print("search queue: %d representatives (OP=0: %d, order-only: %d), family reach %d functions" % (
            len(q), sum(e["kind"] == "OP=0" for e in q), sum(e["kind"] == "order-only" for e in q),
            sum(e["fanout"] for e in q)))
        qshapes = {fan[e["addr"]][0] for e in q if e["addr"] in fan}
        print("paid plan targets that are queued or share a queued shape: %d (must be 0)" % sum(
            x in {e["addr"] for e in q} or (x in fan and fan[x][0] in qshapes) for x in planned))
        tried = campaign.attempted()
        never = [e for e in q if not tried.get(e["addr"])]
        print("queued after a paid attempt: haiku %d, deepseek %d; never tried by a paid tier: %d (family reach %d)" % (
            sum("haiku" in tried.get(e["addr"], ()) for e in q), sum("deepseek" in tried.get(e["addr"], ()) for e in q),
            len(never), sum(e["fanout"] for e in never)))

    print("\n== step 3: mutator")
    res = []
    if os.path.isdir(MUTATE):
        for d in sorted(os.listdir(MUTATE)):
            p = os.path.join(MUTATE, d, "result.json")
            if os.path.exists(p):
                res.append(json.load(open(p)))
    if not res:
        print("no mutator results yet (mutate.py writes logs/mutate/<ADDR>/result.json)")
        return
    fan3 = campaign.shape_fanout([r["addr"] for r in res])
    for r in res:
        s, b = r.get("start") or {}, r.get("best") or {}
        print("  %s %-9s %6d checks  start OP=%s REG=%s MOVED=%s -> best OP=%s REG=%s MOVED=%s  family %d%s%s" % (
            r["addr"], r["status"], r.get("checks", 0), s.get("op"), s.get("reg"), s.get("moved"),
            b.get("op"), b.get("reg"), b.get("moved"), fan3[r["addr"]][1],
            "  de-hack" if r.get("dehack") else "", "  registered" if r.get("registered") else ""))
    m = [r for r in res if r["status"] == "MATCH"]
    new = [r for r in m if not r.get("dehack")]
    print("matched %d/%d targets: %d new (family reach %d functions), %d hacks made honest" % (
        len(m), len(res), len(new), sum(fan3[r["addr"]][1] for r in new), len(m) - len(new)))
    left = [r for r in res if r["status"] != "MATCH" and (r.get("best") or {}).get("op") is not None]
    if left:
        print("unmatched: best OP=0 %d, OP 1-2 %d, OP>2 %d; REG+MOVED gained on %d of %d" % (
            sum(r["best"]["op"] == 0 for r in left), sum(0 < r["best"]["op"] <= 2 for r in left),
            sum(r["best"]["op"] > 2 for r in left),
            sum(gained(r) for r in left), len(left)))


def gained(r):
    """Did the mutator improve on its start (fewer OP, or as many OP and fewer REG+MOVED)?"""
    s, b = r.get("start") or {}, r.get("best") or {}
    if s.get("op") is None or b.get("op") is None:
        return False
    return (b["op"], b["reg"] + b["moved"]) < (s["op"], s["reg"] + s["moved"])


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("census")
    c.add_argument("--sample", type=int, default=100)
    c.add_argument("--jobs", type=int, default=16)
    c.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    census(a)


if __name__ == "__main__":
    main()
