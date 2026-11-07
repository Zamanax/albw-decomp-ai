#!/usr/bin/env python
"""Campaign driver: one round of the cost-routed multi-agent matching loop.

  python tools/campaign.py next    [--refine N] [--haiku N] [--deepseek N] [--batch N]
  campaign.run_round(agent, log)   (in an omp Python eval cell: spawns and supervises the plan)
  python tools/campaign.py harvest [--commit]
  python tools/campaign.py status

A round is: free work first, then a small paid plan, then a harvest.

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
     tried) ignore attempts made before the form's `since`, take up to REOPEN_SHARE[tier] of each tier's
     slots first, and their prompt names the form.
     Routing (the cost rule):
       haiku    - first attempt on anything <= HAIKU_MAX_WORDS words (cheap, ~$0.01-0.05/agent,
                  HAIKU_PER_AGENT targets per agent, grouped by twin origin);
       deepseek - at most MAX_DEEPSEEK per round (hard cap), one target per agent, only for
                  functions Haiku already missed or that are too large for Haiku, with a start at
                  most DEEPSEEK_MAX_OP structural OPs away (~$0.10-0.30/agent, ~50-70% hit rate).
     A function is never sent twice to the same tier (except across a reopen).
  5. writes logs/campaign/plan.json (+ a copy per round) and, per target, logs/manual/<ADDR>/CONTEXT.md
     (tools/context.py: disassembly, references vs the start source, related matched sources).

Agents read docs/AGENT_BRIEF.md and write logs/manual/<ADDR>/REPORT.json per target, so results
survive lost agent handles, crashed kernels and rate-limited agents.

`run_round(agent, log)` (eval kernel only: it needs omp's agent())
  Rolling window of --batch Haiku agents (a new one starts as soon as any finishes) plus all DeepSeek
  agents; TIME[tier] = (wrap-up message, hard stop) per agent; a stopped agent's unreported targets
  get a timeout REPORT.json from their best logged check. Logs events live and a progress table of
  the running agents every minute (fn.py check_log.jsonl: checks and best pct per target).

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

MODELS = {"haiku": "anthropic/claude-haiku-5-5",
          "deepseek": "openrouter/deepseek/deepseek-v4.1-flash-1017"}
MAX_DEEPSEEK = 4          # hard cap per round (cost + rate limits)
# Measured on rounds 1-14 (505 Haiku, 42 DeepSeek targets): Haiku matched 33-37% of functions <= 40 words,
# 18% at 41-80 and 6% (4/70) at 81-160; 27% as an agent's only target but 15% with 2 and 7% with 3
# (later targets get the leftovers of the budget). DeepSeek matched 72% at OP 6-20 but 22% above OP 20.
HAIKU_MAX_WORDS = 80
HAIKU_PER_AGENT = 1
DEEPSEEK_MAX_OP = 20
# Share of each tier's slots that reopened functions (shared/reopen.json: a header form proven after they
# were tried or ranked) take first; the rest is ranked by measured EV. Measured over every harvested
# Haiku target of rounds 1-19, split by the target's size and whether it was reopened:
#     <=40 words  reopened 13/40 = 33%   regular 105/327 = 32%
#     41-80       reopened  5/99 =  5%   regular  47/269 = 17%
#     81-160      reopened  0/36 =  0%   regular   4/70 =  6%
# Size is the signal; reopened status only matters at 41-80 (a retry is harder than a first try).
# The previous 100%-reopened share was calibrated on rounds 17-18, when the reopened pool happened to
# be the <=40 band; the round-22 forms reopened 41-80/81-160 targets, which the table says are 0-5%.
REOPEN_SHARE = {"haiku": 0.25, "deepseek": 0.5}
REOPEN_MAX_WORDS = 80    # 81-160 reopened: 0/36 measured; the regular Haiku cap is the same
BUDGET = {"haiku": (40, 12), "deepseek": (60, 15)}   # (max checks per target, stop after N stale)
# (wrap-up message, hard stop) in seconds of agent wall clock. Measured over 630 targets of rounds 1-13
# (check_log.jsonl): Haiku's first match comes at p50 0.3 / p90 1.5 / max 20 min after its first check,
# DeepSeek's at p50 5 / max 20 min, while the slowest agents ran 40-70 min - a tail that held up whole
# rounds and produced nothing.
TIME = {"haiku": (900, 1200), "deepseek": (1500, 2100)}
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
    """addr -> sorted names of the reopen forms whose markers occur in the function's words."""
    num = lambda x: int(x, 16) if isinstance(x, str) else x
    by_word, by_call, insn = collections.defaultdict(set), collections.defaultdict(set), []
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
        insn += [(name, num(m), num(v)) for m, v in f.get("insn", [])]
    out = {}
    for a in addrs:
        s, e = fn.func_range(int(a, 16))
        got = set()
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
                m = re.search(r"0x%s: refine best \d+/(\d+) words, (\d+) differing" % x, t["prompt"])
                if not m:
                    continue
                sb, ob = bucket(int(m.group(1)), SIZE_EDGES), bucket(int(m.group(2)), OP_EDGES)
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
        src = "%s (language %s)" % (t.get("start") or "logs/refine/%s/best.c" % t["addr"], t["ext"])
        org = t["origin"].split(":", 1)[1] if t["origin"].startswith("twin:") else "none (synth skeleton)"
        lines.append("- 0x%s: refine best %d/%d words, %d differing instructions. Start: %s. Twin: %s. "
                     "Context: logs/manual/%s/CONTEXT.md (disassembly, what the target references and whether "
                     "the start names it, related matched sources) - read it before anything else."
                     % (t["addr"], t["words"], t["total"], t["n_op"], src, org, t["addr"]))
        if t["fanout"] > 1:
            lines.append("  Family: %d functions share this exact shape; a match here is cloned to all of "
                         "them, so it is worth %dx your effort. Name every extern by its address."
                         % (t["fanout"], t["fanout"]))
        forms = reopen_forms()
        for f in t.get("forms", []):
            lines.append("  This function %s" % forms[f]["hint"])
    if retry:
        lines += ["", "A smaller model already tried these and missed: read logs/manual/<ADDR>/ first "
                  "(REPORT.prev.json, best.*, *.txt check logs) and do not repeat its variants; question "
                  "the twin and the signature, re-derive from `fn.py show`."]
    return "\n".join(lines)


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
    reopened = {x: min(forms[f]["since"] for f in fs) for x, fs in hits.items()}
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
    cands = {"haiku": [], "deepseek": []}
    for t in pool:
        if t["shape"] in dead or t["shape"] in queued_shapes or t["addr"] in queued:
            continue
        tiers = tried.get(t["addr"], set()) | (shape_tiers[t["shape"]] if t["fanout"] > 1 else set())
        if "deepseek" in tiers:
            continue
        # a reopened target's best source predates the header form, so its structural OP says nothing
        # about how close it is now: the size cap is raised and the DeepSeek OP gate does not apply
        if "haiku" in tiers or t["total"] > (REOPEN_MAX_WORDS if t["forms"] else HAIKU_MAX_WORDS):
            if not t["forms"] and t["n_op"] > DEEPSEEK_MAX_OP:
                continue
            tier = "deepseek"
        else:
            tier = "haiku"
        t["p"] = p_hit(tier, t["total"], t["n_op"])
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
    # Haiku: the regular pool is on by default (<=40 words 32%, 41-80 17% measured); REOPEN_SHARE caps
    # the reopened retries at a quarter of the slots, since 41-80+ reopened targets convert at 0-5%
    hk = pick(cands["haiku"], a.haiku, "haiku", a.haiku_regular)
    print("hit model (tier, words <= 20/40/80/160/more: matches/attempts): " + "  ".join(
        "%s %s %d/%d" % (k[0][:2], ("<=20", "<=40", "<=80", "<=160", ">160")[k[1]], m, n)
        for k, (m, n) in sorted(rates.items())))
    print("reopened (shared/reopen.json): %d in the pool, %d eligible, %d planned (%s)" % (
        len(hits), sum(bool(t["forms"]) for c in cands.values() for t in c), sum(bool(t["forms"]) for t in hk + ds),
        ", ".join("%s %d" % (f, sum(f in t["forms"] for t in hk + ds)) for f in forms)))

    prev = json.load(open(PLAN)).get("round", 0) if os.path.exists(PLAN) else 0
    rnd = 1 + max([e.get("round", 0) for e in ledger()] + [prev])
    tasks = []
    tag = time.strftime("%m%d%H%M")   # labels must be unique across sessions: the harness keys agents by label
    for t in ds:
        tasks.append(dict(name="c%s_ds_%s" % (tag, t["addr"]), tier="deepseek", model=MODELS["deepseek"],
                          addrs=[t["addr"]], prompt=task_prompt(rnd, "deepseek", [t], retry="haiku" in tried.get(t["addr"], ()))))
    groups = collections.OrderedDict()
    for t in hk:
        groups.setdefault(t["origin"], []).append(t)
    for org, ts in groups.items():
        for i in range(0, len(ts), HAIKU_PER_AGENT):
            ch = ts[i:i + HAIKU_PER_AGENT]
            tasks.append(dict(name="c%s_hk_%s" % (tag, ch[0]["addr"]), tier="haiku", model=MODELS["haiku"],
                              addrs=[x["addr"] for x in ch], prompt=task_prompt(rnd, "haiku", ch, retry=False)))

    # stale reports would be harvested as this round's answer: set them aside; remember where each
    # target's check logs end, so live progress and timeout reports count only this round's checks;
    # and precompute each target's CONTEXT.md (saves the agents their first 5-10 orientation turns)
    index = context.related_index()
    start_of = {x["addr"]: x.get("start") for x in pool}
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
    plan = dict(round=rnd, created=time.strftime("%Y-%m-%d %H:%M:%S"), batch=a.batch, tasks=tasks)
    json.dump(plan, open(PLAN, "w"), indent=1)
    json.dump(plan, open(os.path.join(CAMP, "plan_round%03d.json" % rnd), "w"), indent=1)
    print("round %d plan: %d haiku agents (%d functions), %d deepseek agents; family reach %d functions"
          % (rnd, sum(t["tier"] == "haiku" for t in tasks), len(hk), len(ds),
             sum(t["fanout"] for t in hk + ds)))
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

    A rolling window, not batches: up to plan["batch"] Haiku agents run at once and a new one starts
    the moment any finishes; every DeepSeek agent starts at once (MAX_DEEPSEEK caps them). An agent
    past its soft limit (plan task soft_s) gets WRAP_UP once; past hard_s it is stopped and each of its
    targets without a REPORT.json gets a timeout MISS carrying the best logged check, so harvest records
    it instead of re-planning it. Events are logged as they happen, and every table_every seconds a
    table of the running agents with each target's checks and best logged pct (fn.py check_log.jsonl).
    Results stay file-based: a dead kernel loses nothing, run it again and only unreported tasks start."""
    plan = json.load(open(PLAN))
    if plan.get("harvested"):
        log("round %d is already harvested. NEXT  uv run python tools/campaign.py next" % plan["round"])
        return
    rerun = time.strftime("r%H%M") if plan.get("started") else ""   # labels must stay unique
    plan["started"] = plan.get("started") or time.strftime("%Y-%m-%d %H:%M:%S")
    json.dump(plan, open(PLAN, "w"), indent=1)
    todo = [t for t in plan["tasks"] if not all(reported(x) for x in t["addrs"])]
    queue = {tier: [t for t in todo if t["tier"] == tier] for tier in ("deepseek", "haiku")}
    slots = {"deepseek": MAX_DEEPSEEK, "haiku": plan.get("batch", 20)}
    total = {tier: len(q) for tier, q in queue.items()}
    done = collections.Counter()
    running, t_start, t_table = {}, time.time(), 0.0
    log("round %d: %d haiku + %d deepseek agents to run (%d already reported), window %d haiku"
        % (plan["round"], total["haiku"], total["deepseek"], len(plan["tasks"]) - len(todo), slots["haiku"]))

    def tag(t):
        return "%s %s" % ("ds" if t["tier"] == "deepseek" else "hk", "+".join(t["addrs"]))

    def outcomes(t):
        return ", ".join("%s %s" % (x, reported(x) or "NOREPORT") for x in t["addrs"])

    while any(queue.values()) or running:
        now = time.time()
        for tier, q in queue.items():
            while q and sum(r["t"]["tier"] == tier for r in running.values()) < slots[tier]:
                t = q.pop(0)
                running[t["name"]] = dict(t=t, t0=now, wrapped=False,
                                          h=spawn(t["prompt"], label=t["name"] + rerun, model=t["model"]))
        for name, r in list(running.items()):
            t, el = r["t"], now - r["t0"]
            if r["h"].done():
                try:
                    r["h"].wait(1)   # consume the reply: results are read from REPORT.json, not messages
                except Exception:
                    pass
                why = "done"
            elif el > t.get("hard_s", TIME[t["tier"]][1]):
                try:
                    r["h"].cancel()
                except Exception:
                    pass
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
            log("[%s] %-4s %s  %s  -> %s" % (mmss(now - t_start), why, tag(t), mmss(el), outcomes(t)))
        if running and now - t_table >= table_every:
            t_table = now
            rep = collections.Counter(s for t in plan["tasks"] for x in t["addrs"] for s in [reported(x)] if s)
            run_n = collections.Counter(r["t"]["tier"] for r in running.values())
            lines = ["[%s] haiku %d/%d done, %d running, %d queued | deepseek %d/%d done, %d running | reports: %s"
                     % (mmss(now - t_start), done["haiku"], total["haiku"], run_n["haiku"], len(queue["haiku"]),
                        done["deepseek"], total["deepseek"], run_n["deepseek"],
                        ", ".join("%s %d" % kv for kv in sorted(rep.items())) or "none yet")]
            for r in sorted(running.values(), key=lambda r: r["t0"]):
                t, cells = r["t"], []
                for x in t["addrs"]:
                    n, b = progress(x, t.get("log_base", {}).get(x))
                    st = reported(x)
                    cells.append("%s %s" % (x, st if st else "%2d checks best %s" % (
                        n, ("MATCH" if b["match"] else "%.1f%%" % b["pct"]) if b else "-")))
                lines.append("   %-2s %6s%s  %s" % ("ds" if t["tier"] == "deepseek" else "hk", mmss(now - r["t0"]),
                                                    "*" if r["wrapped"] else " ", " | ".join(cells)))
            log("\n".join(lines))
        if running or any(queue.values()):
            time.sleep(poll)
    rep = collections.Counter(reported(x) or "NOREPORT" for t in plan["tasks"] for x in t["addrs"])
    log("round %d finished in %s: %s. NEXT  uv run python tools/campaign.py harvest --commit"
        % (plan["round"], mmss(time.time() - t_start), ", ".join("%s %d" % kv for kv in sorted(rep.items()))))


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
                rows.append((addr, t["tier"], "NOREPORT", ""))
                continue
            try:
                r = json.load(open(rp))
            except Exception:
                rows.append((addr, t["tier"], "BADREPORT", ""))
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
            rows.append((addr, t["tier"], outcome, words))

    with open(LEDGER, "a") as fh:
        for addr, tier, outcome, words in rows:
            if outcome not in ("NOREPORT", "ALREADY"):
                fh.write(json.dumps(dict(addr=addr, tier=tier, round=rnd, outcome=outcome,
                                         words=words, t=time.strftime("%Y-%m-%d %H:%M"))) + "\n")
    cloned = famclone_apply()
    junk = clean_root()
    audit = run([PY, os.path.join(ROOT, "tools", "audit.py")])
    clean = "RESULT: CLEAN (0 errors" in audit

    c = collections.Counter((tier, o) for _, tier, o, _ in rows)
    for tier in ("haiku", "deepseek"):
        n = sum(v for (ti, _), v in c.items() if ti == tier)
        if n:
            print("%-8s %3d targets: %s" % (tier, n, ", ".join("%s %d" % (o, v) for (ti, o), v in sorted(c.items()) if ti == tier)))
    print("famclone: %d more registered" % cloned)
    if junk:
        print("removed stray root files: %s" % junk)
    for addr, tier, outcome, words in rows:
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
        msg = "Campaign round %d: %d matches (haiku %d, deepseek %d, famclone %d)%s" % (
            rnd, total, got["haiku"], got["deepseek"], cloned,
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
    for tier in ("haiku", "deepseek"):
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
    n.add_argument("--haiku", type=int, default=60, help="Haiku target functions in the plan")
    n.add_argument("--deepseek", type=int, default=MAX_DEEPSEEK, help="DeepSeek agents (capped at %d)" % MAX_DEEPSEEK)
    n.add_argument("--batch", type=int, default=20, help="agents spawned concurrently")
    n.add_argument("--no-haiku-regular", dest="haiku_regular", action="store_false",
                   help="reopened targets only: the regular pool is 32%% at <=40 words and 17%% at 41-80 "
                        "(rounds 1-19), so it is on by default and REOPEN_SHARE caps the retries")
    h = sub.add_parser("harvest")
    h.add_argument("--commit", action="store_true")
    h.add_argument("--force", action="store_true", help="harvest a round again")
    sub.add_parser("status")
    a = ap.parse_args()
    {"next": cmd_next, "harvest": cmd_harvest, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()
