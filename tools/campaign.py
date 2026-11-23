#!/usr/bin/env python
"""Campaign driver: the cost-routed multi-agent matching loop.

  campaign.run_loop(agent, log)    (in an omp Python eval cell: rounds until nothing is left, no model turns)
  python tools/campaign.py next    [--screen N] [--haiku N] [--haiku-rest] [--deepseek N] [--batch N] [--refine N]
  campaign.run_round(agent, log)   (same kind of cell: spawns and supervises the current plan only)
  python tools/campaign.py harvest [--commit]
  python tools/campaign.py status

A round is: free work first, then a paid plan, then a harvest. run_loop chains rounds.

`next`
  1. famclone --apply: clone existing matches onto shape-identical functions (free).
  2. optional `--refine N`: run refine.py on the next N never-refined candidates (free, CPU only).
  3. score every unmatched function's best source (refine's and the agents', structscore.py:
     fn.py's register-blind STRUCTURE line, cached) and route:
       search queue - OP=0 (only register/order differences left) or OP <= 2 where every OP is a
                  register copy or a flipped branch (structscore.order_only): one representative
                  per shape goes to logs/campaign/search_queue.jsonl for tools/mutate.py (free).
                  Never sent to a paid tier, nor is any member of its shape family. A function whose
                  mutate result is EXHAUSTED leaves the queue and is routed like any other.
  4. build the agent plan from the remaining near-misses. Each candidate is routed to the tier it
     would go to, then ranked within that tier by EV = family size x p, where p is the measured hit
     rate of that tier on past targets of the same size and structural-OP bucket (hit_model(): every
     plan_round*.json joined with the ledger, smoothed toward coarser buckets). One representative
     per shape family is sent; famclone harvests the rest once it matches.
     Reopened functions (shared/reopen.json: they contain a shared-header form proven after they were
     tried) ignore attempts made before the form's `since` (the newest form's, when several apply), take
     up to REOPEN_SHARE[tier] of each tier's slots first, and their prompt names the form.
     Routing (the cost rule; measurements in docs/LESSONS.md "One-turn screen"):
       screen   - every function <= SCREEN_MAX_WORDS words that no tier has tried: ONE Haiku turn without
                  tools writes SCREEN_K candidate sources (~$0.007, ~25 s). run_round compiles them
                  (default flags, a candidate that does not compile again with albw_types.h prepended,
                  then the flag sweep on the best SCREEN_SWEEP), a clean match is registered by harvest,
                  and the best candidate becomes the function's start source;
       haiku    - the full agent (~$0.02-0.04, ~2 min), only for screened functions whose best source
                  is within SCREEN_PASS structural OPs (the agent matches ~20% of those, ~8% at OP 3-5);
                  --haiku-rest adds the functions that failed the gate, up to --haiku-rest-max words
                  (default 40; ~13% for the agent at <= 40, ~5% estimated at 41-80);
       haiku2   - off by default (--haiku2 N): ONE second Haiku agent for a function the Haiku agent
                  missed (<= HAIKU_MAX_WORDS words), starting from the best source so far, with the
                  previous attempt's files named in the prompt; ranked by the Haiku hit model (OP first);
       deepseek - off by default (--deepseek N, hard cap MAX_DEEPSEEK per round), one target per agent,
                  only for functions Haiku already missed or that are too large for Haiku, with a start
                  at most DEEPSEEK_MAX_OP structural OPs away (~$0.10-0.30/agent).
     A function is never sent twice to the same tier (except across a reopen).
  5. writes logs/campaign/plan.json (+ a copy per round) and, per target, logs/manual/<ADDR>/CONTEXT.md
     (tools/context.py: disassembly, references vs the start source, related matched sources).

Haiku and DeepSeek agents read docs/AGENT_BRIEF.md and write logs/manual/<ADDR>/REPORT.json per target. A
screen agent gets everything in its prompt (logs/manual/<ADDR>/screen/PROMPT.md), writes
logs/manual/<ADDR>/screen/s1..sK.{c,cpp}, and run_round writes its REPORT.json from the compiled
candidates. Results therefore survive lost agent handles, crashed kernels and rate-limited agents.

`run_round(agent, log)` (eval kernel only: it needs omp's agent())
  Rolling window of --batch Anthropic agents (Haiku agents and screens share it; a new one starts as soon
  as any finishes) plus all DeepSeek agents; TIME[tier] = (wrap-up message, hard stop) per agent; a
  stopped agent's unreported targets get a timeout REPORT.json from their best logged check. Logs events
  live and a progress table of the running agents every minute (fn.py check_log.jsonl).

`run_loop(agent, log, rounds=0, screen=300, haiku=80, deepseek=0, haiku_rest=False, haiku_rest_max=40)` (eval kernel only)
  harvest --commit -> next -> run_round with `mutate.py queue --register` alongside, until the plan is
  empty (or `rounds` rounds), then `mutate.py tidy --register` and a last harvest. No model turn is spent
  between rounds. Stops when most targets of a round got no report (rate limit, credits).

`harvest`
  Reads the REPORT.json of every planned target, scans the claimed source for forbidden
  constructs, registers MATCH claims through worklist.py register (which re-verifies), records
  every outcome in logs/campaign/ledger.jsonl, runs famclone again, removes stray files agents
  left in the repo root, runs audit.py, and with --commit commits functions.json + src/work8/auto.
  Then prints the top form candidates from recent misses (tools/formmine.py -> logs/campaign/forms.md):
  markers whose users match far below the rate expected for their size, i.e. a missing header form.
  A target without a REPORT.json (agent failed, rate limited) is not recorded, so it is retried.

`status`
  Ledger totals and hit rate per tier, what the current plan contains, and while it runs the live
  progress of every unreported target (checks and best pct from fn.py's check logs).
"""
import argparse
import collections
import json
import os
import re
import shutil
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fn  # noqa: E402
import context  # noqa: E402
import famclone  # noqa: E402
import structscore  # noqa: E402

ROOT = fn.ROOT
PY = sys.executable
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
CAMP = os.path.join(ROOT, "logs", "campaign")
PLAN = os.path.join(CAMP, "plan.json")
LEDGER = os.path.join(CAMP, "ledger.jsonl")
QUEUE = structscore.QUEUE
MANUAL = os.path.join(ROOT, "logs", "manual")
CAND_FILE = os.path.join(ROOT, "logs", "triage", "unindexed_candidate.txt")

MODELS = {"screen": "anthropic/claude-haiku-5-5",
          "haiku": "anthropic/claude-haiku-5-5",
          "haiku2": "anthropic/claude-haiku-5-5",
          "deepseek": "openrouter/deepseek/deepseek-v4.1-flash-1017"}
TIERS = ("screen", "haiku", "haiku2", "deepseek")   # cheapest first
POOL = {"screen": "anthropic", "haiku": "anthropic", "haiku2": "anthropic", "deepseek": "openrouter"}   # run_round's concurrency windows
MAX_DEEPSEEK = 4          # hard cap per round (cost + rate limits)
# Measured on rounds 1-14 (505 Haiku, 42 DeepSeek targets): Haiku matched 33-37% of functions <= 40 words,
# 18% at 41-80 and 6% (4/70) at 81-160; 27% as an agent's only target but 15% with 2 and 7% with 3
# (later targets get the leftovers of the budget). DeepSeek matched 72% at OP 6-20 but 22% above OP 20.
HAIKU_MAX_WORDS = 80
HAIKU_PER_AGENT = 1
DEEPSEEK_MAX_OP = 20
# One-turn screen, measured 2026-11-15 on 80 Haiku targets of rounds 15-18 (all 37 the agent matched and 43
# of the 167 it missed; docs/LESSONS.md "One-turn screen"). One Haiku turn without tools, writing 4 candidates,
# costs $0.0075 and 24 s and matches ~3% of the pool outright; three such turns with feedback reach 11%
# against the agent's 18% at the same price, so the turn does not replace the agent. Its best candidate's
# structural OP predicts the agent instead. SCREEN_PASS is that gate per size band, (max words, max OP of
# the best source). Re-measured on rounds 26-39 (623 gated agents after a screen): OP 0-2 matched 18% at
# <= 40 words and 20% at 41-80, OP 3-5 at 41-80 only 7.8% (11/141), so 41-80 now gates at OP <= 2 too.
SCREEN_K = 4
SCREEN_PASS = ((40, 2), (80, 2))
# Screens above 60 words: rounds 26-39 gave 4 direct matches in 638 screens at 61-80 words (0.6%), $0.75 per
# match with their agents against $0.14-0.32 below; they are not screened (and so never reach the agent).
SCREEN_MAX_WORDS = 60
# Integer/float typedefs live in albw_types.h, which vec3.h and the sead headers do not include: of the 219
# screens of rounds 26-39 whose candidates all failed to compile, 82 compiled with it. A candidate that fails
# to compile without the include is retried with it prepended (kept only if that compiles).
TYPES_INCLUDE = '#include "albw_types.h"\n'
SCREEN_SWEEP = 2          # candidates (best first at the default flags) that also get the flag sweep
SCREEN_HEALTHY = 0.75     # share of a round's screens that must leave candidates before a blank one is a MISS
BRIEF_SECTIONS = ("Shared library", "Done means", "Honesty", "Proven constructs")   # inlined in the screen prompt
# Share of each tier's slots that reopened functions (shared/reopen.json: a header form proven after they
# were tried or ranked) take first; the rest is ranked by measured EV. Measured over every harvested
# Haiku target of rounds 1-19, split by the target's size and whether it was reopened:
#     <=40 words  reopened 13/40 = 33%   regular 105/327 = 32%
#     41-80       reopened  5/99 =  5%   regular  47/269 = 17%
#     81-160      reopened  0/36 =  0%   regular   4/70 =  6%
# Size is the signal; reopened status only matters at 41-80 (a retry is harder than a first try).
# The previous 100%-reopened share was calibrated on rounds 17-18, when the reopened pool happened to
# be the <=40 band; the round-22 forms reopened 41-80/81-160 targets, which the table says are 0-5%.
REOPEN_SHARE = {"screen": 0.0, "haiku": 0.25, "haiku2": 0.25, "deepseek": 0.5}
REOPEN_MAX_WORDS = 80    # 81-160 reopened: 0/36 measured; the regular Haiku cap is the same
BUDGET = {"haiku": (40, 12), "haiku2": (40, 12), "deepseek": (60, 15)}   # (max checks per target, stop after N stale)
# (wrap-up message, hard stop) in seconds of agent wall clock. Measured over 630 targets of rounds 1-13
# (check_log.jsonl): Haiku's first match comes at p50 0.3 / p90 1.5 / max 20 min after its first check,
# DeepSeek's at p50 5 / max 20 min, while the slowest agents ran 40-70 min - a tail that held up whole
# rounds and produced nothing.
# A screen is one turn: p50 24 s, p90 48 s over 211 turns. It has no wrap-up (soft = hard).
TIME = {"screen": (240, 240), "haiku": (900, 1200), "haiku2": (900, 1200), "deepseek": (1500, 2100)}
WRAP_UP = ("WRAP UP: your time budget is used. Stop exploring now. Write logs/manual/<ADDR>/REPORT.json for "
           "every target (MATCH only if fn.py check printed RESULT: MATCH and IDENTITY ... 0 MISMATCH for that "
           "file and flags, otherwise MISS with your best words), then reply DONE. You will be stopped in %d minutes.")

FORBID = re.compile(r"__attribute__\(\(weak\)\)|\b__weak\b|__schedule_barrier|\b__asm\b|\basm\s*\(|"
                    r"\bvolatile\b|\bperm_t\b|&\s*0xffffffff\b|while\s*\(\s*0\s*\)|\b(\w+)\s*\?\s*\1\s*:\s*0\b", re.I)


# ------------------------------------------------------------------ state

def load_status():
    return json.load(open(os.path.join(ROOT, "functions.json")))


def ledger():
    if not os.path.exists(LEDGER):
        return []
    return [json.loads(l) for l in open(LEDGER) if l.strip()]


def attempted(reopened=None):
    """addr -> set of tiers that already tried it (ledger + pre-campaign logs/manual dirs). For an addr in
    `reopened` (addr -> since, "YYYY-MM-DD HH:MM"), attempts before `since` do not count: they were made
    before a shared-header form it needs existed (shared/reopen.json)."""
    reopened = reopened or {}
    tried = collections.defaultdict(set)
    for e in ledger():
        if e["addr"] in reopened and e.get("t", "") < reopened[e["addr"]]:
            continue
        tried[e["addr"]].add(e["tier"])
    if os.path.isdir(MANUAL):
        for d in os.listdir(MANUAL):
            a = d.replace("0x", "").upper()
            if not re.fullmatch(r"[0-9A-F]{8}", a) or a in reopened:   # pre-campaign dirs predate any reopen
                continue
            p = os.path.join(MANUAL, d)
            src = lambda q: os.path.isdir(q) and any(f.endswith((".c", ".cpp")) for f in os.listdir(q))
            if src(p):                              # an agent that died before writing code tried nothing
                tried[a].add("haiku")
            if src(os.path.join(p, "ds")):
                tried[a].add("deepseek")
    return tried


def reopen_forms():
    """Committed shared/reopen.json: header forms proven after their functions were tried."""
    p = os.path.join(ROOT, "shared", "reopen.json")
    return {k: v for k, v in json.load(open(p)).items() if not k.startswith("_")} if os.path.exists(p) else {}


def form_hits(addrs, forms):
    """addr -> sorted names of the reopen forms whose markers occur in the function's words.

    Marker kinds: `words`, `calls`, `vtable_slot`, `insn` and `addrs` (an explicit address list, for a
    form whose inlined code has no distinguishing word, call or instruction — e.g. the type-node walk)."""
    num = lambda x: int(x, 16) if isinstance(x, str) else x
    by_word, by_call, insn = collections.defaultdict(set), collections.defaultdict(set), []
    explicit = collections.defaultdict(set)
    slots = [(name, num(o), num(v)) for name, f in forms.items() for o, v in f.get("vtable_slot", [])]
    if slots:   # a literal pointing at an ro vtable with that slot value
        end = fn.RA + fn.RS
        for vt in range(fn.RA, end - 4, 4):
            for name, o, v in slots:
                if vt + o + 4 <= end and fn.rd32(vt + o) == v:
                    by_word[vt].add(name)
    for name, f in forms.items():
        for w in f.get("words", []):
            by_word[num(w)].add(name)
        for c in f.get("calls", []):
            by_call[num(c)].add(name)
        for x in f.get("addrs", []):
            explicit[num(x)].add(name)
        insn += [(name, num(m), num(v)) for m, v in f.get("insn", [])]
    out = {}
    for a in addrs:
        s, e = fn.func_range(int(a, 16))
        got = set(explicit.get(num(a), set()))
        for x in range(s, e, 4):
            w = fn.rd32(x)
            got |= by_word.get(w, set())
            if by_call and (w & 0x0E000000) == 0x0A000000 and (w >> 28) != 0xF:
                imm = w & 0xFFFFFF
                got |= by_call.get(x + 8 + ((imm - 0x1000000 if imm & 0x800000 else imm) << 2), set())
            got |= {name for name, m, v in insn if w & m == v}
        if got:
            out[a] = sorted(got)
    return out


SIZE_EDGES, OP_EDGES, PSEUDO = (20, 40, 80, 160), (5, 10, 20), 5.0


def hit_model():
    """Measured match probability per (tier, size bucket, OP bucket): every past plan (target size and
    structural OP as planned) joined with its ledger outcome. A Haiku agent counts only its first target
    (later ones got the leftovers of a shared budget). Each level is smoothed toward the coarser one with
    PSEUDO pseudo-observations: tier -> tier x size -> tier x size x OP. Returns (p(tier, words, op), rows)."""
    out = {(e["addr"], e["round"], e["tier"]): e["outcome"] for e in ledger()}
    cnt = collections.defaultdict(lambda: [0, 0])
    bucket = lambda v, edges: sum(v > x for x in edges)
    for f in sorted(os.listdir(CAMP)):
        if not re.fullmatch(r"plan_round\d+\.json", f):
            continue
        p = json.load(open(os.path.join(CAMP, f)))
        for t in p["tasks"]:
            for i, x in enumerate(t["addrs"]):
                o = out.get((x, p["round"], t["tier"]))
                if (t["tier"] == "haiku" and i) or o not in ("MATCH", "MISS", "TIMEOUT", "REFUSED"):
                    continue
                size = (t.get("sizes") or {}).get(x)   # [words, structural OP] as planned
                if size is None:                       # plans older than the screen tier: in the prompt
                    m = re.search(r"0x%s: refine best \d+/(\d+) words, (\d+) differing" % x, t.get("prompt", ""))
                    if not m:
                        continue
                    size = (int(m.group(1)), int(m.group(2)))
                sb, ob = bucket(size[0], SIZE_EDGES), bucket(size[1], OP_EDGES)
                for k in ((t["tier"],), (t["tier"], sb), (t["tier"], sb, ob)):
                    cnt[k][0] += o == "MATCH"
                    cnt[k][1] += 1

    def p(tier, words, op):
        sb, ob = bucket(words, SIZE_EDGES), bucket(op, OP_EDGES)
        m, n = cnt[(tier,)]
        q = m / float(n) if n else 0.2
        for k in ((tier, sb), (tier, sb, ob)):
            m, n = cnt[k]
            q = (m + PSEUDO * q) / (n + PSEUDO)
        return q
    return p, {k: tuple(v) for k, v in cnt.items() if len(k) == 2}


def parked():
    """Committed list of documented dead ends (shared/parked.json): never sent to any tier."""
    p = os.path.join(ROOT, "shared", "parked.json")
    return {k for k in json.load(open(p)) if not k.startswith("_")} if os.path.exists(p) else set()


def near_misses(status):
    out = []
    rdir = os.path.join(ROOT, "logs", "refine")
    for a in os.listdir(rdir):
        p = os.path.join(rdir, a, "state.json")
        if a in status or not os.path.exists(p):
            continue
        st = json.load(open(p))
        b = st.get("best") or {}
        if not b.get("total") or b.get("err") or b.get("match"):
            continue
        out.append(dict(addr=a, words=b["words"], total=b["total"], n_op=b["n_op"],
                        ext=st.get("ext", ".c"), origin=st.get("origin", "")))
    return out


def shape_fanout(addrs):
    """addr -> (shape key, number of unmatched functions with that shape), counted over every unmatched
    candidate (logs/triage/unindexed_candidate.txt) plus addrs, not only over addrs."""
    status, addrs = load_status(), set(addrs)
    every = addrs | {l.split()[0] for l in open(CAND_FILE) if l.strip()}
    keys = {}
    for a in every:
        if a in status and a not in addrs:
            continue
        try:
            keys[a] = famclone.words(int(a, 16))
        except Exception:
            keys[a] = ("?", a)
    count = collections.Counter(keys.values())
    return {a: (keys[a], count[keys[a]]) for a in addrs}


def mutate_exhausted(addr):
    p = os.path.join(structscore.MUTATE, addr, "result.json")
    return os.path.exists(p) and json.load(open(p)).get("status") == "EXHAUSTED"


def search_queue(best, fan):
    """Representatives (one per shape) whose best source differs only by registers/order. Writes QUEUE."""
    q = {}
    for addr, (src, sc, _) in best.items():
        if sc.get("err") or sc["match"] or mutate_exhausted(addr):
            continue
        kind = "OP=0" if sc["op"] == 0 else "order-only" if structscore.order_only(sc) else None
        if kind is None:
            continue
        shape, fanout = fan[addr]
        if shape not in q or structscore.rank(sc) < structscore.rank(q[shape]["sc"]):
            q[shape] = dict(addr=addr, sc=sc, src=src, kind=kind, fanout=fanout)
    out = []
    for shape, e in q.items():
        sc, src = e["sc"], e["src"]
        out.append(dict(addr=e["addr"], kind=e["kind"], path=os.path.relpath(src["path"], ROOT),
                        flags=src["flags"], cc=src["cc"], origin=src["origin"], op=sc["op"], reg=sc["reg"],
                        moved=sc["moved"], total=sc["n"], ops=sc["ops"], fanout=e["fanout"]))
    out.sort(key=lambda e: (-e["fanout"], e["op"], e["reg"] + e["moved"]))
    with open(QUEUE, "w") as fh:
        for e in out:
            fh.write(json.dumps(e) + "\n")
    return out


def check_logs(addr):
    """{path: lines} of every fn.py check_log.jsonl under logs/manual/<addr> (agents may use subdirs)."""
    out = {}
    for root, _, files in os.walk(os.path.join(MANUAL, addr)):
        if "check_log.jsonl" in files:
            p = os.path.join(root, "check_log.jsonl")
            out[os.path.relpath(p, ROOT)] = open(p, errors="replace").read().splitlines()
    return out


def progress(addr, base=None):
    """This round's fn.py checks of addr (lines past the plan's baseline): checks, best pct and its source."""
    n, best = 0, None
    for rel, lines in check_logs(addr).items():
        for l in lines[(base or {}).get(rel, 0):]:
            try:
                e = json.loads(l)
            except ValueError:
                continue
            if e.get("addr") != addr:
                continue
            n += 1
            if best is None or (e.get("match"), e.get("pct", 0)) > (best.get("match"), best.get("pct", 0)):
                best = dict(e, path=os.path.join(os.path.dirname(rel), e.get("src", "")))
    return n, best


def timeout_report(addr, base=None):
    """REPORT.json for a target whose agent hit the hard time limit, from its best logged check: a MATCH
    if a check matched (harvest re-verifies it through worklist.py register), else a MISS."""
    rp = os.path.join(MANUAL, addr, "REPORT.json")
    if os.path.exists(rp):
        return False
    n, b = progress(addr, base)
    os.makedirs(os.path.dirname(rp), exist_ok=True)
    json.dump(dict(addr=addr, status="MATCH" if b and b.get("match") else "MISS", timeout=True, checks=n,
                   file=b["path"].replace("\\", "/") if b else None, flags=b.get("flags") if b else None,
                   words="%.1f%%" % b["pct"] if b else "", note="stopped at the hard time limit; best logged check"),
              open(rp, "w"), indent=1)
    return True

# ------------------------------------------------------------------ free stages

def run(argv, timeout=3600):
    r = subprocess.run(argv, capture_output=True, text=True, cwd=ROOT, timeout=timeout)
    return r.stdout


def famclone_apply():
    out = run([PY, os.path.join(ROOT, "tools", "famclone.py"), "--apply"])
    m = re.search(r"(\d+) registered", out)
    return int(m.group(1)) if m else 0


def refine_batch(n, jobs=10):
    status = load_status()
    cands = [l.split()[0] for l in open(CAND_FILE) if l.strip()]
    batch = [a for a in cands if a not in status
             and not os.path.exists(os.path.join(ROOT, "logs", "refine", a, "state.json"))][:n]

    def go(a):
        try:
            subprocess.run([PY, os.path.join(ROOT, "tools", "refine.py"), "0x" + a, "--budget", "60"],
                           capture_output=True, cwd=ROOT, timeout=900)
        except subprocess.TimeoutExpired:
            pass
        p = os.path.join(ROOT, "logs", "refine", a, "state.json")
        return a, (json.load(open(p)).get("status") if os.path.exists(p) else None)

    with ThreadPoolExecutor(jobs) as ex:
        res = list(ex.map(go, batch))
    got = 0
    for a, s in res:
        if s == "MATCH":
            out = run([PY, os.path.join(ROOT, "tools", "worklist.py"), "register", "0x" + a])
            got += "%s -> honest" % a in out
    return len(batch), got


# ------------------------------------------------------------------ plan

def task_prompt(rnd, tier, targets, retry):
    checks, stall = BUDGET[tier]
    soft, hard = TIME[tier]
    lines = ["Read docs/AGENT_BRIEF.md first and follow it exactly.", "",
             "Round %d, tier %s. Budget: at most %d oracle checks per target; stop a target after %d "
             "checks without improvement. Time: about %d minutes for the whole task; a WRAP UP message "
             "arrives then, and you are stopped at %d minutes." % (rnd, tier, checks, stall, soft // 60, hard // 60),
             "", "Targets:"]
    for t in targets:
        start = t.get("start") or "logs/refine/%s/best.c" % t["addr"]
        src = "%s (language %s)" % (start, os.path.splitext(start)[1] if t.get("start") else t["ext"])
        org = t["origin"].split(":", 1)[1] if t["origin"].startswith("twin:") else "none (synth skeleton)"
        lines.append("- 0x%s: refine best %d/%d words, %d differing instructions. Start: %s. Twin: %s. "
                     "Context: logs/manual/%s/CONTEXT.md (disassembly, what the target references and whether "
                     "the start names it, related matched sources) - read it before anything else."
                     % (t["addr"], t["words"], t["total"], t.get("n_op", -1), src, org, t["addr"]))
        if "/screen/" in start.replace("\\", "/"):
            lines.append("  The start is the best of %d candidates a one-turn screen wrote; the others are next "
                         "to it in logs/manual/%s/screen/." % (SCREEN_K, t["addr"]))
        ops = t.get("ops") or []
        if ops:
            lines.append("  Remaining structural diff (original `-`, start `+`): "
                         + ", ".join("`%s`" % o for o in ops))
            lines.append("  Repair class: %s - %s" % (context.classify_ops(ops),
                                                      context.PLAYBOOK[context.classify_ops(ops)]))
        if t["fanout"] > 1:
            lines.append("  Family: %d functions share this exact shape; a match here is cloned to all of "
                         "them, so it is worth %dx your effort. Name every extern by its address."
                         % (t["fanout"], t["fanout"]))
        forms = reopen_forms()
        for f in t.get("forms", []):
            lines.append("  This function %s" % forms[f]["hint"])
    if retry:
        who = "A previous Haiku agent" if tier == "haiku2" else "A smaller model"
        lines += ["", who + " already tried these and missed: read logs/manual/<ADDR>/ first "
                  "(REPORT.prev.json, best.*, *.txt check logs) and do not repeat its variants; question "
                  "the twin and the signature, re-derive from `fn.py show`."]
    return "\n".join(lines)


# ------------------------------------------------------------------ screen (one Haiku turn without tools)

def screen_dir(addr):
    """A subdirectory on purpose: attempted() reads a source directly under logs/manual/<ADDR>/ as an
    agent's attempt, and a screen must not use up the Haiku agent's turn."""
    return os.path.join(MANUAL, addr, "screen")


def screen_candidates(addr):
    d = screen_dir(addr)
    return sorted(os.path.join(d, f) for f in (os.listdir(d) if os.path.isdir(d) else [])
                  if re.fullmatch(r"s\d+\.(?:c|cpp)", f))


def screen_pass(t):
    """The full agent's gate: the best known source is within SCREEN_PASS structural OPs for its size."""
    return next((t["n_op"] <= op for words, op in SCREEN_PASS if t["total"] <= words), False)


def brief_sections(names=BRIEF_SECTIONS):
    """The named `## ` sections of docs/AGENT_BRIEF.md: a screen turn follows the agents' rules and proven
    constructs without spending a turn on reading the brief."""
    text = open(os.path.join(ROOT, "docs", "AGENT_BRIEF.md"), encoding="utf-8").read()
    parts = {m.group(1): m.group(0).strip() for m in re.finditer(r"^## ([^\n]*)\n.*?(?=^## |\Z)", text, re.S | re.M)}
    out = []
    for n in names:
        hit = [v for k, v in parts.items() if k.startswith(n)]
        if not hit:
            sys.exit("docs/AGENT_BRIEF.md has no '## %s' section, which the screen prompt inlines" % n)
        out.append(hit[0])
    return "\n\n".join(out)


def screen_prompt(t, brief):
    """The whole task in one message: the agent reads nothing and runs nothing."""
    addr = t["addr"]
    read = lambda rel: open(os.path.join(ROOT, rel), encoding="utf-8", errors="replace").read().rstrip()
    start = t.get("start") or "logs/refine/%s/best.c" % addr
    ext = os.path.splitext(start)[1] if t.get("start") else t["ext"]
    files = ", ".join("`logs/manual/%s/screen/s%d.{c|cpp}`" % (addr, i) for i in range(1, SCREEN_K + 1))
    forms = reopen_forms()
    lines = [
        "ONE-TURN TASK. Do NOT read any file, do NOT run any command, do NOT search. Everything you need is in "
        "this message.",
        "",
        "Write %d DIFFERENT candidate sources for function 0x%s of a matching decompilation (armcc 4.1 b1049, "
        "ARM, flags `%s`). Each must compile to exactly the target's bytes; a harness compiles and checks them "
        "after you finish. In a SINGLE response, call the write tool %d times in parallel: %s (`.cpp` if the "
        "source is C++ or includes a shared header, `.c` for C99). Then answer `DONE`. No explanations."
        % (SCREEN_K, addr, DEFAULT_FLAGS, SCREEN_K, files),
        "",
        "Rules for every candidate:",
        "- Define the function as `func_%s`; name every extern after its address (`func_XXXXXXXX`, "
        "`data_XXXXXXXX`, `ro_XXXXXXXX`)." % addr,
        "- Write it from the disassembly: every callee, offset, immediate, literal-pool value, store order and "
        "return value must agree with it. The start source below is often a different function of similar "
        "shape; reuse its declarations only where they fit.",
        "- The %d candidates must differ in ways that change codegen (named locals vs direct expressions, "
        "statement order, if/else polarity, early return vs nested if, pointer local vs member access, C vs "
        "C++ with a header type, signed vs unsigned, return type), not in comments or names." % SCREEN_K,
        "- Self-contained: declare every type and extern you use, or include a shared header named below. "
        "The typedefs u8/s8/u16/s16/u32/s32/u64/f32 come only from `#include \"albw_types.h\"`: vec3.h and the "
        "sead headers do not provide them.",
    ]
    lines += ["- This function %s" % forms[f]["hint"] for f in t.get("forms", [])]
    lines += ["", brief, "", "# Target context", "", read("logs/manual/%s/CONTEXT.md" % addr), ""]
    if os.path.exists(os.path.join(ROOT, start)):   # a start lost with its directory: CONTEXT.md is enough
        lines += ["# Start source (%s)" % ext, "", "```", read(start), "```", ""]
    return "\n".join(lines)


def screen_reports(addrs):
    """Write REPORT.json for screened targets from their candidates: every candidate at the default flags,
    then the flag sweep (refine.flag_variants) on the SCREEN_SWEEP best of each target without a match.
    MATCH needs a byte match with 0 identity mismatches and no forbidden construct; harvest re-verifies and
    registers it. Otherwise MISS carrying the best candidate, which structscore.agent_sources then offers
    as the function's start source. A target without candidates gets no report here (see run_round)."""
    import refine
    variants = refine.flag_variants(DEFAULT_FLAGS)
    cands = {a: screen_candidates(a) for a in addrs}
    dirty = {p: bool(FORBID.search(open(p, errors="replace").read())) for ps in cands.values() for p in ps}
    scores = collections.defaultdict(dict)   # addr -> {(path, flags): score}

    def score(keys):
        items = [dict(addr=int(a, 16), path=p, flags=fl, cc=structscore.DEFAULT_CC) for a, p, fl in keys]
        for (a, p, fl), sc in zip(keys, structscore.score_many(items)):
            if not sc.get("err"):
                scores[a][(p, fl)] = sc

    def clean(a, k):
        sc = scores[a][k]
        return sc["match"] and not sc.get("identity_bad") and not dirty[k[0]]

    def ranked(a):
        return sorted(scores[a], key=lambda k: (not clean(a, k), dirty[k[0]], structscore.rank(scores[a][k])))

    score([(a, p, DEFAULT_FLAGS) for a in addrs for p in cands[a]])
    # a candidate that does not compile is most often only missing the typedefs: retry it with albw_types.h
    retry = {}
    for a in addrs:
        for p in cands[a]:
            text = open(p, "rb").read()
            if not any(k[0] == p for k in scores[a]) and b"albw_types.h" not in text:
                retry[(a, p)] = text
                open(p, "wb").write(TYPES_INCLUDE.encode() + text)
    if retry:
        score([(a, p, DEFAULT_FLAGS) for a, p in retry])
        for (a, p), text in retry.items():
            if not any(k[0] == p for k in scores[a]):
                open(p, "wb").write(text)   # still does not compile: leave the agent's text as written
    sweep = []
    for a in addrs:
        ks = ranked(a)
        if ks and not clean(a, ks[0]):
            sweep += [(a, p, fl) for p, _ in ks[:SCREEN_SWEEP] for fl in variants[1:]]
    score(sweep)
    for a in addrs:
        if not cands[a]:
            continue
        ks = ranked(a)
        best = ks[0] if ks else None
        sc = scores[a][best] if best else {}
        compiled = len({p for p, _ in ks})
        rep = dict(addr=a, tier="screen", status="MATCH" if best and clean(a, best) else "MISS",
                   file=os.path.relpath(best[0], ROOT).replace("\\", "/") if best else None,
                   flags=best[1] if best else None,
                   words="%d/%d" % (sc["words"], sc["total"]) if best else "",
                   screen=dict(candidates=len(cands[a]), compiled=compiled,
                               op=sc.get("op"), reg=sc.get("reg"), moved=sc.get("moved")),
                   note="screen: %d candidates, %d compiled%s" % (
                       len(cands[a]), compiled,
                       "; best OP=%d REG=%d MOVED=%d" % (sc["op"], sc["reg"], sc["moved"]) if best else ""))
        json.dump(rep, open(os.path.join(MANUAL, a, "REPORT.json"), "w"), indent=1)


def screen_blank(addr):
    """MISS for a screen whose agent finished a healthy round without leaving a candidate."""
    json.dump(dict(addr=addr, tier="screen", status="MISS", file=None, flags=None, words="",
                   screen=dict(candidates=0, compiled=0, op=None, reg=None, moved=None),
                   note="screen: the agent wrote no candidate"),
              open(os.path.join(MANUAL, addr, "REPORT.json"), "w"), indent=1)


def cmd_next(a):
    os.makedirs(CAMP, exist_ok=True)
    cloned = famclone_apply()
    print("famclone: %d registered" % cloned)
    if a.refine:
        n, got = refine_batch(a.refine)
        print("refine: %d candidates, %d MATCH registered" % (n, got))

    status = load_status()
    pool = near_misses(status)
    forms = reopen_forms()
    hits = form_hits([t["addr"] for t in pool], forms)
    # the newest form decides: an attempt made after an older form but before a newer one still lacked it
    reopened = {x: max(forms[f]["since"] for f in fs) for x, fs in hits.items()}
    tried, skip = attempted(reopened), parked()
    best = structscore.best_structures(status, progress=True)
    fan = shape_fanout(sorted({t["addr"] for t in pool} | set(best)))
    queue = search_queue(best, fan)
    queued = {e["addr"] for e in queue}
    queued_shapes = {fan[e["addr"]][0] for e in queue}
    print("search queue: %d functions (OP=0: %d, OP<=2 order-only: %d), family reach %d -> %s"
          % (len(queue), sum(e["kind"] == "OP=0" for e in queue), sum(e["kind"] == "order-only" for e in queue),
             sum(e["fanout"] for e in queue), os.path.relpath(QUEUE, ROOT)))
    if a.queue_only:  # refresh logs/campaign/search_queue.jsonl only: no famclone, no plan, no REPORT moves
        return
    for t in pool:
        t["shape"], t["fanout"] = fan[t["addr"]]
        sc = best.get(t["addr"], (None, {"err": "unscored"}, None))[1]
        if not sc.get("err"):
            t["n_op"] = sc["op"]  # structural OP of the best source (refine's or an agent's)
            t["words"] = sc["words"]
            t["ops"] = (sc.get("ops") or [])[:6]
        it = best.get(t["addr"], (None, None, None))[0]
        t["start"] = os.path.relpath(it["path"], ROOT) if it and it.get("path") else None
        t["forms"] = hits.get(t["addr"], [])

    # history and parking apply to the whole shape family: a sibling of a dead end is the same dead end
    shape_of = lambda a: fan[a][0] if a in fan else famclone.words(int(a, 16))
    shape_tiers = collections.defaultdict(set)
    for addr, tiers in tried.items():
        if addr in status:      # a matched member whose siblings did not clone is no evidence against them
            continue
        try:
            shape_tiers[shape_of(addr)] |= tiers
        except Exception:
            pass
    dead = set()
    for addr in skip:
        try:
            dead.add(shape_of(addr))
        except Exception:
            pass

    # route every candidate to the tier it would go to, then rank each tier by measured EV:
    # family size x the observed hit rate of that tier on functions of this size and structural OP
    p_hit, rates = hit_model()
    cands = {tier: [] for tier in TIERS}
    for t in pool:
        if t["shape"] in dead or t["shape"] in queued_shapes or t["addr"] in queued:
            continue
        tiers = tried.get(t["addr"], set()) | (shape_tiers[t["shape"]] if t["fanout"] > 1 else set())
        if "deepseek" in tiers:
            continue
        # a reopened target's best source predates the header form, so its structural OP says nothing
        # about how close it is now: the size cap is raised and the DeepSeek OP gate does not apply
        if "haiku" in tiers or t["total"] > (REOPEN_MAX_WORDS if t["forms"] else HAIKU_MAX_WORDS):
            if a.haiku2 and "haiku" in tiers and "haiku2" not in tiers and t["total"] <= HAIKU_MAX_WORDS:
                tier = "haiku2"
            elif not t["forms"] and t["n_op"] > DEEPSEEK_MAX_OP:
                continue
            else:
                tier = "deepseek"
        elif "screen" not in tiers:
            if t["total"] > SCREEN_MAX_WORDS:
                continue
            tier = "screen"   # one cheap turn first: its best candidate decides whether the agent is worth it
        elif screen_pass(t) or (a.haiku_rest and t["total"] <= a.haiku_rest_max):
            tier = "haiku"
        else:
            continue
        # haiku2 has no history of its own yet: rank it with the first agent's model (size x OP)
        t["p"] = p_hit("haiku" if tier == "haiku2" else tier, t["total"], t["n_op"])
        t["ev"] = t["fanout"] * t["p"]
        cands[tier].append(t)

    seen_shapes = set()

    def pick(cs, n, tier, regular):
        """Reopened functions first (up to REOPEN_SHARE[tier] of the slots), then, if `regular`, the rest by EV."""
        cs.sort(key=lambda t: (-t["ev"], t["total"]))
        out, ids = [], set()
        passes = ((int(n * REOPEN_SHARE[tier] + 0.5), True),) + (((n, False),) if regular else ())
        for cap, only_reopened in passes:
            for t in cs:
                if len(out) >= cap:
                    break
                if (only_reopened and not t["forms"]) or id(t) in ids or t["shape"] in seen_shapes:
                    continue
                out.append(t)
                ids.add(id(t))
                seen_shapes.add(t["shape"])
        return out
    ds = pick(cands["deepseek"], min(a.deepseek, MAX_DEEPSEEK), "deepseek", True)
    # Haiku: screened functions inside the SCREEN_PASS gate (--haiku-rest: also the <= 40-word ones outside
    # it, ~13% for the agent); REOPEN_SHARE caps the reopened retries at a quarter of the slots
    hk = pick(cands["haiku"], a.haiku, "haiku", a.haiku_regular)
    h2 = pick(cands["haiku2"], a.haiku2, "haiku2", True)
    scr = pick(cands["screen"], a.screen, "screen", True)
    planned = scr + hk + h2 + ds
    print("hit model (tier, words <= 20/40/80/160/more: matches/attempts): " + "  ".join(
        "%s %s %d/%d" % (k[0][:2], ("<=20", "<=40", "<=80", "<=160", ">160")[k[1]], m, n)
        for k, (m, n) in sorted(rates.items())))
    print("reopened (shared/reopen.json): %d in the pool, %d eligible, %d planned (%s)" % (
        len(hits), sum(bool(t["forms"]) for c in cands.values() for t in c), sum(bool(t["forms"]) for t in planned),
        ", ".join("%s %d" % (f, sum(f in t["forms"] for t in planned)) for f in forms)))
    print("eligible: " + ", ".join("%s %d" % (tier, len(cands[tier])) for tier in TIERS))

    prev = json.load(open(PLAN)).get("round", 0) if os.path.exists(PLAN) else 0
    rnd = 1 + max([e.get("round", 0) for e in ledger()] + [prev])
    tasks = []
    tag = time.strftime("%m%d%H%M")   # labels must be unique across sessions: the harness keys agents by label
    sizes = lambda ts: {x["addr"]: [x["total"], x["n_op"]] for x in ts}   # hit_model() reads these back
    for t in ds:
        tasks.append(dict(name="c%s_ds_%s" % (tag, t["addr"]), tier="deepseek", model=MODELS["deepseek"],
                          addrs=[t["addr"]], sizes=sizes([t]),
                          prompt=task_prompt(rnd, "deepseek", [t], retry="haiku" in tried.get(t["addr"], ()))))
    groups = collections.OrderedDict()
    for t in hk:
        groups.setdefault(t["origin"], []).append(t)
    for org, ts in groups.items():
        for i in range(0, len(ts), HAIKU_PER_AGENT):
            ch = ts[i:i + HAIKU_PER_AGENT]
            tasks.append(dict(name="c%s_hk_%s" % (tag, ch[0]["addr"]), tier="haiku", model=MODELS["haiku"],
                              addrs=[x["addr"] for x in ch], sizes=sizes(ch),
                              prompt=task_prompt(rnd, "haiku", ch, retry=False)))
    for t in h2:
        tasks.append(dict(name="c%s_h2_%s" % (tag, t["addr"]), tier="haiku2", model=MODELS["haiku2"],
                          addrs=[t["addr"]], sizes=sizes([t]), prompt=task_prompt(rnd, "haiku2", [t], retry=True)))
    for t in scr:   # the prompt inlines CONTEXT.md, so it is written below, once that exists
        tasks.append(dict(name="c%s_sc_%s" % (tag, t["addr"]), tier="screen", model=MODELS["screen"],
                          addrs=[t["addr"]], sizes=sizes([t]),
                          prompt_file="logs/manual/%s/screen/PROMPT.md" % t["addr"]))

    # stale reports would be harvested as this round's answer: set them aside; remember where each
    # target's check logs end, so live progress and timeout reports count only this round's checks;
    # and precompute each target's CONTEXT.md (saves the agents their first 5-10 orientation turns)
    index = context.related_index()
    by_addr = {x["addr"]: x for x in pool}
    start_of = {x["addr"]: x.get("start") for x in pool}
    brief = brief_sections() if scr else ""
    for t in tasks:
        t["soft_s"], t["hard_s"] = TIME[t["tier"]]
        t["log_base"] = {}
        for addr in t["addrs"]:
            r = os.path.join(MANUAL, addr, "REPORT.json")
            if os.path.exists(r):
                shutil.move(r, os.path.join(MANUAL, addr, "REPORT.prev.json"))
            t["log_base"][addr] = {rel: len(lines) for rel, lines in check_logs(addr).items()}
            start = start_of.get(addr) or ("logs/refine/%s/best.c" % addr)
            context.build(int(addr, 16), start=start if os.path.exists(os.path.join(ROOT, start)) else None, index=index)
            if t["tier"] == "screen":
                # a reopened function is screened again: its old candidates move to screen/prev/ (outside
                # screen_candidates() and attempted()), and a start source among them follows them there
                prev = os.path.join(screen_dir(addr), "prev")
                for old in screen_candidates(addr):
                    os.makedirs(prev, exist_ok=True)
                    shutil.move(old, os.path.join(prev, os.path.basename(old)))
                    rel = os.path.relpath(old, ROOT).replace("\\", "/")
                    if (by_addr[addr].get("start") or "").replace("\\", "/") == rel:
                        by_addr[addr]["start"] = os.path.relpath(os.path.join(prev, os.path.basename(old)), ROOT)
                os.makedirs(screen_dir(addr), exist_ok=True)
                with open(os.path.join(ROOT, t["prompt_file"]), "w", encoding="utf-8", newline="\n") as fh:
                    fh.write(screen_prompt(by_addr[addr], brief))
    plan = dict(round=rnd, created=time.strftime("%Y-%m-%d %H:%M:%S"), batch=a.batch, tasks=tasks)
    json.dump(plan, open(PLAN, "w"), indent=1)
    json.dump(plan, open(os.path.join(CAMP, "plan_round%03d.json" % rnd), "w"), indent=1)
    print("round %d plan: %d screens, %d haiku agents (%d functions), %d haiku2 agents, %d deepseek agents; "
          "family reach %d functions"
          % (rnd, len(scr), sum(t["tier"] == "haiku" for t in tasks), len(hk), len(h2), len(ds),
             sum(t["fanout"] for t in planned)))
    for t in ds:
        print("  deepseek 0x%s  %d/%d words  OP %d  p %.2f  family %d%s" % (
            t["addr"], t["words"], t["total"], t["n_op"], t["p"], t["fanout"],
            ("  reopened: " + ",".join(t["forms"])) if t["forms"] else ""))
    print("NEXT  spawn the plan: in a Python eval cell, campaign.run_round(agent, log) "
          "(see .agents/skills/decomp-campaign), then: uv run python tools/campaign.py harvest --commit")


# ------------------------------------------------------------------ run (inside the omp eval kernel)

def reported(addr):
    p = os.path.join(MANUAL, addr, "REPORT.json")
    if not os.path.exists(p):
        return None
    try:
        r = json.load(open(p))
    except ValueError:
        return "BAD"
    return "TIMEOUT" if r.get("timeout") else str(r.get("status", "?")).upper()


def mmss(s):
    return "%d:%02d" % (s // 60, s % 60)


def run_round(spawn, log=print, poll=10, table_every=60):
    """Run the current plan from an omp Python eval cell: `campaign.run_round(agent, log)`.

    A rolling window, not batches: up to plan["batch"] Anthropic agents run at once (Haiku agents first,
    then screens) and a new one starts the moment any finishes; every DeepSeek agent starts at once
    (MAX_DEEPSEEK caps them). An agent past its soft limit (plan task soft_s) gets WRAP_UP once; past
    hard_s it is stopped and each of its targets without a REPORT.json gets a timeout MISS carrying the
    best logged check, so harvest records it instead of re-planning it. A finished screen's candidates are
    compiled here and its REPORT.json written (screen_reports). Events are logged as they happen, and
    every table_every seconds a table of the running agents with each target's checks and best logged pct.
    Results stay file-based: a dead kernel loses nothing, run it again and only unreported tasks start."""
    plan = json.load(open(PLAN))
    if plan.get("harvested"):
        log("round %d is already harvested. NEXT  uv run python tools/campaign.py next" % plan["round"])
        return
    rerun = time.strftime("r%H%M") if plan.get("started") else ""   # labels must stay unique
    plan["started"] = plan.get("started") or time.strftime("%Y-%m-%d %H:%M:%S")
    json.dump(plan, open(PLAN, "w"), indent=1)
    screens = [x for t in plan["tasks"] if t["tier"] == "screen" for x in t["addrs"]]
    late = [x for x in screens if not reported(x) and screen_candidates(x)]
    if late:   # their agents finished before an earlier run of this cell died: only the compile is left
        screen_reports(late)
    todo = [t for t in plan["tasks"] if not all(reported(x) for x in t["addrs"])]
    queue = {tier: [t for t in todo if t["tier"] == tier] for tier in ("deepseek", "haiku", "haiku2", "screen")}
    slots = {"openrouter": MAX_DEEPSEEK, "anthropic": plan.get("batch", 20)}
    total = {tier: len(q) for tier, q in queue.items()}
    short = {"deepseek": "ds", "haiku": "hk", "haiku2": "h2", "screen": "sc"}
    done = collections.Counter()
    running, t_start, t_table = {}, time.time(), 0.0
    if screens:
        poll = min(poll, 3)   # a screen lasts ~24 s: a 10 s poll leaves its slot idle a third of the time
    scorer, scoring = ThreadPoolExecutor(1), []   # candidates compile off the loop, so slots refill meanwhile
    log("round %d: %s to run (%d tasks already reported), window %d Anthropic agents"
        % (plan["round"], " + ".join("%d %s" % (total[tier], tier) for tier in TIERS),
           len(plan["tasks"]) - len(todo), slots["anthropic"]))

    def tag(t):
        return "%s %s" % (short[t["tier"]], "+".join(t["addrs"]))

    def outcomes(t):
        return ", ".join("%s %s" % (x, reported(x) or "NOREPORT") for x in t["addrs"])

    while any(queue.values()) or running or scoring:
        now = time.time()
        for tier, q in queue.items():
            while q and sum(POOL[r["t"]["tier"]] == POOL[tier] for r in running.values()) < slots[POOL[tier]]:
                t = q.pop(0)
                prompt = (open(os.path.join(ROOT, t["prompt_file"]), encoding="utf-8").read()
                          if t.get("prompt_file") else t["prompt"])
                running[t["name"]] = dict(t=t, t0=now, wrapped=False,
                                          h=spawn(prompt, label=t["name"] + rerun, model=t["model"]))
        finished = []
        for name, r in list(running.items()):
            t, el = r["t"], now - r["t0"]
            if r["h"].done():
                try:
                    r["h"].wait(1)   # consume the reply: results are read from files, not messages
                except Exception:
                    pass
                why = "done"
            elif el > t.get("hard_s", TIME[t["tier"]][1]):
                try:
                    r["h"].cancel()
                except Exception:
                    pass
                if t["tier"] != "screen":
                    for x in t["addrs"]:
                        timeout_report(x, t.get("log_base", {}).get(x))
                why = "STOPPED at hard limit"
            else:
                if el > t.get("soft_s", TIME[t["tier"]][0]) and not r["wrapped"]:
                    left = (t.get("hard_s", TIME[t["tier"]][1]) - el) / 60
                    try:
                        r["h"].send(WRAP_UP % max(1, round(left)))
                    except Exception as e:
                        log("  wrap-up to %s failed: %s" % (tag(t), e))
                    r["wrapped"] = True
                    log("[%s] wrap-up sent  %s  (%s in)" % (mmss(now - t_start), tag(t), mmss(el)))
                continue
            del running[name]
            done[t["tier"]] += 1
            finished.append((t, why, el))
        got = [x for t, _, _ in finished if t["tier"] == "screen" for x in t["addrs"] if screen_candidates(x)]
        if got:
            blank = sum(t["tier"] == "screen" for t, _, _ in finished) - len(got)
            scoring.append((scorer.submit(screen_reports, got), got, blank))
        for job in [j for j in scoring if j[0].done()]:
            scoring.remove(job)
            job[0].result()
            c = collections.Counter(reported(x) for x in job[1])
            log("[%s] screens %d/%d: +%d compiled (%s)%s" % (
                mmss(now - t_start), done["screen"], total["screen"], len(job[1]),
                ", ".join("%s %d" % kv for kv in sorted(c.items())),
                ", %d without candidates" % job[2] if job[2] else ""))
        for t, why, el in finished:
            if t["tier"] != "screen":
                log("[%s] %-4s %s  %s  -> %s" % (mmss(now - t_start), why, tag(t), mmss(el), outcomes(t)))
        if running and now - t_table >= table_every:
            t_table = now
            rep = collections.Counter(s for t in plan["tasks"] for x in t["addrs"] for s in [reported(x)] if s)
            run_n = collections.Counter(r["t"]["tier"] for r in running.values())
            lines = ["[%s] %s | reports: %s" % (mmss(now - t_start), " | ".join(
                "%s %d/%d done, %d running, %d queued" % (tier, done[tier], total[tier], run_n[tier], len(queue[tier]))
                for tier in TIERS if total[tier]), ", ".join("%s %d" % kv for kv in sorted(rep.items())) or "none yet")]
            for r in sorted(running.values(), key=lambda r: r["t0"]):
                t, cells = r["t"], []
                if t["tier"] == "screen":   # one turn each: the header line counts them
                    continue
                for x in t["addrs"]:
                    n, b = progress(x, t.get("log_base", {}).get(x))
                    st = reported(x)
                    cells.append("%s %s" % (x, st if st else "%2d checks best %s" % (
                        n, ("MATCH" if b["match"] else "%.1f%%" % b["pct"]) if b else "-")))
                lines.append("   %-2s %6s%s  %s" % (short[t["tier"]], mmss(now - r["t0"]),
                                                    "*" if r["wrapped"] else " ", " | ".join(cells)))
            log("\n".join(lines))
        if running or any(queue.values()) or scoring:
            time.sleep(poll)
    scorer.shutdown()
    # a screen that left no candidate is a MISS only in a healthy round: after a rate limit or an API
    # failure nothing was tried, so those targets stay unreported and the next plan takes them again
    blank = [x for x in screens if not reported(x)]
    if blank and 1 - len(blank) / float(len(screens)) >= SCREEN_HEALTHY:
        for x in blank:
            screen_blank(x)
    rep = collections.Counter(reported(x) or "NOREPORT" for t in plan["tasks"] for x in t["addrs"])
    log("round %d finished in %s: %s. NEXT  uv run python tools/campaign.py harvest --commit"
        % (plan["round"], mmss(time.time() - t_start), ", ".join("%s %d" % kv for kv in sorted(rep.items()))))


def run_loop(spawn, log=print, rounds=0, screen=300, haiku=80, deepseek=0, haiku_rest=False, haiku_rest_max=40,
             mutate_budget=1000, haiku2=0):
    """Rounds with no model turn between them, from one omp Python eval cell (cell timeout 0):
    `campaign.run_loop(agent, log)`.

    Each round: harvest --commit (the previous round, or one left unfinished), next with these sizes, then
    run_round while `mutate.py queue --register --budget mutate_budget` searches the register/order queue
    (42 of the mutator's 48 matches needed <= 1,000 checks, a third of the default budget). Ends when the
    plan is empty or after `rounds` rounds, with `mutate.py tidy --register` and a last harvest --commit.
    Stops early when more than half of a round's targets got no report: the agents are failing (Anthropic
    429, OpenRouter 402), and the unreported targets are simply planned again by the next run."""
    tool = lambda name, *args: run([PY, os.path.join(ROOT, "tools", name)] + [str(x) for x in args], timeout=None)
    tail = lambda out, n: "\n".join("  " + l for l in out.strip().splitlines()[-n:])
    n = 0
    while True:
        log("harvest:\n" + tail(tool("campaign.py", "harvest", "--commit"), 14))
        args = ["--screen", screen, "--haiku", haiku, "--haiku2", haiku2, "--deepseek", deepseek] + (
            ["--haiku-rest", "--haiku-rest-max", haiku_rest_max] if haiku_rest else [])
        log("next:\n" + tail(tool("campaign.py", "next", *args), 8))
        plan = json.load(open(PLAN))
        if plan.get("harvested") or not plan["tasks"]:
            log("nothing left to plan for these tiers")
            break
        mlog = os.path.join(CAMP, "mutate_round%03d.log" % plan["round"])
        with open(mlog, "w") as fh:
            mut = subprocess.Popen([PY, os.path.join(ROOT, "tools", "mutate.py"), "queue", "--register",
                                    "--budget", str(mutate_budget)], cwd=ROOT, stdout=fh, stderr=subprocess.STDOUT)
            run_round(spawn, log)
            mut.wait()
        res = collections.Counter(re.findall(r"^[0-9A-F]{8}: (MATCH|IDENTITY|EXHAUSTED)\b", open(mlog).read(), re.M))
        log("mutator: %s" % (", ".join("%s %d" % kv for kv in sorted(res.items())) or "queue empty"))
        addrs = [x for t in plan["tasks"] for x in t["addrs"]]
        lost = sum(not reported(x) for x in addrs)
        n += 1
        if lost > len(addrs) / 2.0:
            log("STOP: %d of %d targets got no report - the agents are failing (rate limit? credits?). "
                "Run the cell again later; nothing is lost." % (lost, len(addrs)))
            break
        if rounds and n >= rounds:
            break
    log("tidy:\n" + tail(tool("mutate.py", "tidy", "--register"), 3))
    log("harvest:\n" + tail(tool("campaign.py", "harvest", "--commit"), 14))


# ------------------------------------------------------------------ harvest

def canon_flags(fl):
    t = fl.split()
    o = lambda x: (0 if x.startswith("--cpu") else 1 if x.startswith("--fpmode") else 2 if x.startswith("--fpu")
                   else 3 if x.startswith("--apcs") else 4 if x.startswith("-O") else 5)
    return " ".join(sorted(t, key=lambda x: (o(x), t.index(x))))


def clean_root():
    out = run(["git", "status", "--short"])
    junk = [l[3:] for l in out.splitlines() if l.startswith("??") and "/" not in l[3:].rstrip("/")]
    for f in junk:
        p = os.path.join(ROOT, f)
        if os.path.isfile(p):
            os.remove(p)
    return junk


def cmd_harvest(a):
    if not os.path.exists(PLAN):
        print("no plan yet. NEXT  uv run python tools/campaign.py next")
        return
    plan = json.load(open(PLAN))
    rnd = plan["round"]
    if plan.get("harvested") and not a.force:
        print("round %d is already harvested (use --force to redo). NEXT  uv run python tools/campaign.py next" % rnd)
        return
    status = load_status()
    rows, got = [], collections.Counter()
    for t in plan["tasks"]:
        for addr in t["addrs"]:
            rp = os.path.join(MANUAL, addr, "REPORT.json")
            if not os.path.exists(rp):
                rows.append((addr, t["tier"], "NOREPORT", "", None))
                continue
            try:
                r = json.load(open(rp))
            except Exception:
                rows.append((addr, t["tier"], "BADREPORT", "", None))
                continue
            outcome, words = ("TIMEOUT" if r.get("timeout") else "MISS"), str(r.get("words", ""))
            if addr in status:
                outcome = "ALREADY"
            elif str(r.get("status", "")).upper() == "MATCH" and r.get("file"):
                src = os.path.join(ROOT, r["file"].replace("\\", "/").strip("`"))
                flags = canon_flags(r.get("flags") or DEFAULT_FLAGS)
                bad = ([m.group(0) for m in FORBID.finditer(open(src, errors="replace").read())]
                       if os.path.exists(src) else ["missing file"])
                if bad:
                    outcome = "REJECTED"
                    words = "forbidden: %s" % bad[:3]
                else:
                    out = run([PY, os.path.join(ROOT, "tools", "worklist.py"), "register", "0x" + addr,
                               "--src", src, "--flags", flags])
                    if "%s -> honest" % addr in out:
                        outcome = "MATCH"
                        got[t["tier"]] += 1
                    else:
                        outcome = "REFUSED"
                        words = (out.strip().splitlines() or [""])[0][:80]
            rows.append((addr, t["tier"], outcome, words, (r.get("screen") or {}).get("op")))

    with open(LEDGER, "a") as fh:
        for addr, tier, outcome, words, op in rows:
            if outcome not in ("NOREPORT", "ALREADY"):
                e = dict(addr=addr, tier=tier, round=rnd, outcome=outcome, words=words, t=time.strftime("%Y-%m-%d %H:%M"))
                if op is not None:
                    e["op"] = op   # a screen's best candidate: structural OPs from the target
                fh.write(json.dumps(e) + "\n")
    cloned = famclone_apply()
    junk = clean_root()
    audit = run([PY, os.path.join(ROOT, "tools", "audit.py")])
    clean = "RESULT: CLEAN (0 errors" in audit

    c = collections.Counter((tier, o) for _, tier, o, _, _ in rows)
    for tier in TIERS:
        n = sum(v for (ti, _), v in c.items() if ti == tier)
        if n:
            print("%-8s %3d targets: %s" % (tier, n, ", ".join("%s %d" % (o, v) for (ti, o), v in sorted(c.items()) if ti == tier)))
    print("famclone: %d more registered" % cloned)
    if junk:
        print("removed stray root files: %s" % junk)
    for addr, tier, outcome, words, _ in rows:
        if outcome in ("REJECTED", "REFUSED", "BADREPORT"):
            print("  %s %s %s %s" % (addr, tier, outcome, words))
    print("audit: " + (audit.strip().splitlines() or ["?"])[-1])
    # the misses point at constructs the shared headers lack (tools/formmine.py, logs/campaign/forms.md)
    forms = run([PY, os.path.join(ROOT, "tools", "formmine.py"), "--top", "5"]).splitlines()
    print("form candidates from recent misses (prove on the out-of-line instance, then shared/reopen.json):")
    print("\n".join("  " + l for l in forms if l.startswith("| 00") or l.startswith("(")))
    total = sum(got.values()) + cloned
    plan["harvested"] = True
    json.dump(plan, open(PLAN, "w"), indent=1)
    # also commit what the mutator (or anything else) registered while the round ran
    pending = run(["git", "status", "--porcelain", "functions.json", "src/work8/auto"]).strip()
    if a.commit and (total or pending) and clean:
        run(["git", "add", "functions.json", "src/work8/auto", "shared/construct_exceptions.json"])
        msg = "Campaign round %d: %d matches (screen %d, haiku %d, haiku2 %d, deepseek %d, famclone %d)%s" % (
            rnd, total, got["screen"], got["haiku"], got["haiku2"], got["deepseek"], cloned,
            " + pending registrations (mutator)" if pending and not total else "")
        body = "Registered via tools/campaign.py harvest (worklist.py register re-verifies each: " \
               "RESULT: MATCH, IDENTITY 0 MISMATCH, forbidden-construct scan)."
        r = subprocess.run(["git", "commit", "-q", "-m", msg, "-m", body], cwd=ROOT, capture_output=True, text=True)
        print("committed: " + msg if r.returncode == 0 else "commit failed: " + r.stderr[-200:])
    elif a.commit and not clean:
        print("NOT committed: audit is not clean")
    print("NEXT  uv run python tools/campaign.py next")


# ------------------------------------------------------------------ status

def cmd_status(a):
    led = ledger()
    c = collections.Counter((e["tier"], e["outcome"]) for e in led)
    for tier in TIERS:
        n = sum(v for (t, _), v in c.items() if t == tier)
        m = c[(tier, "MATCH")]
        if n:
            print("%-8s %4d attempts, %4d MATCH (%.0f%%)" % (tier, n, m, 100.0 * m / n))
    if os.path.exists(PLAN):
        p = json.load(open(PLAN))
        done = sum(os.path.exists(os.path.join(MANUAL, x, "REPORT.json")) for t in p["tasks"] for x in t["addrs"])
        tot = sum(len(t["addrs"]) for t in p["tasks"])
        print("current plan: round %d, %d agents, %d/%d targets reported" % (p["round"], len(p["tasks"]), done, tot))
        if not p.get("harvested"):   # live progress of the unreported targets, from fn.py's check logs
            for t in p["tasks"]:
                for x in t["addrs"]:
                    if not reported(x):
                        n, b = progress(x, t.get("log_base", {}).get(x))
                        print("  %-8s %s  %2d checks  best %s" % (t["tier"], x, n, (
                            "MATCH" if b["match"] else "%.1f%%" % b["pct"]) if b else "-"))
    st = load_status()
    print("functions.json: %d honest, %d hack" % (sum(v.get("status") == "honest" for v in st.values()),
                                                   sum(v.get("status") == "hack" for v in st.values())))


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next")
    n.add_argument("--queue-only", action="store_true",
                   help="only re-score and rewrite the search queue (no famclone, no plan)")
    n.add_argument("--refine", type=int, default=0, help="refine N new candidates first (free)")
    n.add_argument("--screen", type=int, default=300,
                   help="one-turn Haiku screens of never-tried functions <= %d words" % HAIKU_MAX_WORDS)
    n.add_argument("--haiku", type=int, default=80, help="full Haiku agents (screened functions inside the gate)")
    n.add_argument("--haiku-rest", action="store_true",
                   help="also plan the screened functions outside the gate, up to --haiku-rest-max words")
    n.add_argument("--haiku-rest-max", type=int, default=SCREEN_PASS[0][0],
                   help="word cap for --haiku-rest (default %(default)s: ~13%% for the agent; 41-80 ~5%%)")
    n.add_argument("--haiku2", type=int, default=0,
                   help="second Haiku agents for functions <= %d words the Haiku agent missed" % HAIKU_MAX_WORDS)
    n.add_argument("--deepseek", type=int, default=0, help="DeepSeek agents (capped at %d)" % MAX_DEEPSEEK)
    n.add_argument("--batch", type=int, default=20, help="agents spawned concurrently")
    n.add_argument("--no-haiku-regular", dest="haiku_regular", action="store_false",
                   help="full Haiku agents for reopened functions only (shared/reopen.json)")
    h = sub.add_parser("harvest")
    h.add_argument("--commit", action="store_true")
    h.add_argument("--force", action="store_true", help="harvest a round again")
    sub.add_parser("status")
    a = ap.parse_args()
    {"next": cmd_next, "harvest": cmd_harvest, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()
