#!/usr/bin/env python
"""Campaign driver: one round of the cost-routed multi-agent matching loop.

  python tools/campaign.py next    [--refine N] [--haiku N] [--deepseek N] [--batch N]
  python tools/campaign.py harvest [--commit]
  python tools/campaign.py status

A round is: free work first, then a small paid plan, then a harvest.

`next`
  1. famclone --apply: clone existing matches onto shape-identical functions (free).
  2. optional `--refine N`: run refine.py on the next N never-refined candidates (free, CPU only).
  3. build the agent plan from refine's near-misses, ranked by expected value
     EV = family size x (1 - differing instructions / words). One representative per shape
     family is sent; famclone harvests the rest once it matches.
     Routing (the cost rule):
       haiku    - first attempt on anything <= HAIKU_MAX_WORDS words (cheap, ~$0.01-0.05/agent,
                  up to 3 targets per agent, grouped by twin origin);
       deepseek - at most MAX_DEEPSEEK per round (hard cap), one target per agent, only for
                  functions Haiku already missed or that are too large for Haiku, highest EV
                  first (~$0.10-0.30/agent, ~80% hit rate on Haiku misses).
     A function is never sent twice to the same tier.
  4. writes logs/campaign/plan.json (+ a copy per round) and prints how to spawn it.

Agents read docs/AGENT_BRIEF.md and write logs/manual/<ADDR>/REPORT.json per target, so results
survive lost agent handles, crashed kernels and rate-limited agents.

`harvest`
  Reads the REPORT.json of every planned target, scans the claimed source for forbidden
  constructs, registers MATCH claims through worklist.py register (which re-verifies), records
  every outcome in logs/campaign/ledger.jsonl, runs famclone again, removes stray files agents
  left in the repo root, runs audit.py, and with --commit commits functions.json + src/work8/auto.
  A target without a REPORT.json (agent failed, rate limited) is not recorded, so it is retried.

`status`
  Ledger totals and hit rate per tier, and what the current plan contains.
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
import famclone  # noqa: E402

ROOT = fn.ROOT
PY = sys.executable
DEFAULT_FLAGS = "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections"
CAMP = os.path.join(ROOT, "logs", "campaign")
PLAN = os.path.join(CAMP, "plan.json")
LEDGER = os.path.join(CAMP, "ledger.jsonl")
MANUAL = os.path.join(ROOT, "logs", "manual")
CAND_FILE = os.path.join(ROOT, "logs", "triage", "unindexed_candidate.txt")

MODELS = {"haiku": "anthropic/claude-haiku-5-5",
          "deepseek": "openrouter/deepseek/deepseek-v4.1-flash-1017"}
MAX_DEEPSEEK = 4          # hard cap per round (cost + rate limits)
HAIKU_MAX_WORDS = 160     # larger functions skip Haiku (measured: Haiku wins are <= ~110 words)
HAIKU_PER_AGENT = 3
BUDGET = {"haiku": (40, 12), "deepseek": (60, 15)}   # (max checks per target, stop after N stale)

FORBID = re.compile(r"__attribute__\(\(weak\)\)|\b__weak\b|__schedule_barrier|\b__asm\b|\basm\s*\(|"
                    r"\bvolatile\b|perm_t|&\s*0xffffffff\b|while\s*\(\s*0\s*\)|\b(\w+)\s*\?\s*\1\s*:\s*0\b", re.I)


# ------------------------------------------------------------------ state

def load_status():
    return json.load(open(os.path.join(ROOT, "functions.json")))


def ledger():
    if not os.path.exists(LEDGER):
        return []
    return [json.loads(l) for l in open(LEDGER) if l.strip()]


def attempted():
    """addr -> set of tiers that already tried it (ledger + pre-campaign logs/manual dirs)."""
    tried = collections.defaultdict(set)
    for e in ledger():
        tried[e["addr"]].add(e["tier"])
    if os.path.isdir(MANUAL):
        for d in os.listdir(MANUAL):
            a = d.replace("0x", "").upper()
            if not re.fullmatch(r"[0-9A-F]{8}", a):
                continue
            p = os.path.join(MANUAL, d)
            src = lambda q: os.path.isdir(q) and any(f.endswith((".c", ".cpp")) for f in os.listdir(q))
            if src(p):                              # an agent that died before writing code tried nothing
                tried[a].add("haiku")
            if src(os.path.join(p, "ds")):
                tried[a].add("deepseek")
    return tried


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
    """addr -> (shape key, number of unmatched functions with that shape)."""
    keys = {}
    for a in addrs:
        try:
            keys[a] = famclone.words(int(a, 16))
        except Exception:
            keys[a] = ("?", a)
    count = collections.Counter(keys.values())
    return {a: (k, count[k]) for a, k in keys.items()}


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
    lines = ["Read docs/AGENT_BRIEF.md first and follow it exactly.", "",
             "Round %d, tier %s. Budget: at most %d oracle checks per target; stop a target after %d "
             "checks without improvement." % (rnd, tier, checks, stall), "", "Targets:"]
    for t in targets:
        src = "logs/refine/%s/best.c (language %s)" % (t["addr"], t["ext"])
        org = t["origin"].split(":", 1)[1] if t["origin"].startswith("twin:") else "none (synth skeleton)"
        lines.append("- 0x%s: refine best %d/%d words, %d differing instructions. Start: %s. Twin: %s."
                     % (t["addr"], t["words"], t["total"], t["n_op"], src, org))
        if t["fanout"] > 1:
            lines.append("  Family: %d functions share this exact shape; a match here is cloned to all of "
                         "them, so it is worth %dx your effort. Name every extern by its address."
                         % (t["fanout"], t["fanout"]))
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
    tried, skip = attempted(), parked()
    pool = near_misses(status)
    fan = shape_fanout([t["addr"] for t in pool])
    for t in pool:
        t["shape"], t["fanout"] = fan[t["addr"]]
        t["ev"] = t["fanout"] * max(0.05, 1.0 - t["n_op"] / float(t["total"]))
    pool.sort(key=lambda t: (-t["ev"], t["total"]))

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

    seen_shapes, hk, ds = set(), [], []
    n_ds = min(a.deepseek, MAX_DEEPSEEK)
    for t in pool:
        if t["shape"] in seen_shapes or t["shape"] in dead:
            continue
        tiers = tried.get(t["addr"], set()) | (shape_tiers[t["shape"]] if t["fanout"] > 1 else set())
        if "deepseek" in tiers:
            continue
        if "haiku" in tiers or t["total"] > HAIKU_MAX_WORDS:
            if len(ds) < n_ds:
                ds.append(t)
                seen_shapes.add(t["shape"])
            continue
        if len(hk) < a.haiku:
            hk.append(t)
            seen_shapes.add(t["shape"])
        if len(hk) >= a.haiku and len(ds) >= n_ds:
            break

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

    # stale reports would be harvested as this round's answer: set them aside
    for t in tasks:
        for addr in t["addrs"]:
            r = os.path.join(MANUAL, addr, "REPORT.json")
            if os.path.exists(r):
                shutil.move(r, os.path.join(MANUAL, addr, "REPORT.prev.json"))
    plan = dict(round=rnd, created=time.strftime("%Y-%m-%d %H:%M:%S"), batch=a.batch, tasks=tasks)
    json.dump(plan, open(PLAN, "w"), indent=1)
    json.dump(plan, open(os.path.join(CAMP, "plan_round%03d.json" % rnd), "w"), indent=1)
    print("round %d plan: %d haiku agents (%d functions), %d deepseek agents; family reach %d functions"
          % (rnd, sum(t["tier"] == "haiku" for t in tasks), len(hk), len(ds),
             sum(t["fanout"] for t in hk + ds)))
    for t in ds:
        print("  deepseek 0x%s  %d/%d words  family %d" % (t["addr"], t["words"], t["total"], t["fanout"]))
    print("NEXT  spawn the plan (see .agents/skills/decomp-campaign), then: "
          "uv run python tools/campaign.py harvest --commit")


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
            outcome, words = "MISS", str(r.get("words", ""))
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
    total = sum(got.values()) + cloned
    plan["harvested"] = True
    json.dump(plan, open(PLAN, "w"), indent=1)
    if a.commit and total and clean:
        run(["git", "add", "functions.json", "src/work8/auto", "shared/construct_exceptions.json"])
        msg = "Campaign round %d: %d matches (haiku %d, deepseek %d, famclone %d)" % (
            rnd, total, got["haiku"], got["deepseek"], cloned)
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
    st = load_status()
    print("functions.json: %d honest, %d hack" % (sum(v.get("status") == "honest" for v in st.values()),
                                                   sum(v.get("status") == "hack" for v in st.values())))


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next")
    n.add_argument("--refine", type=int, default=0, help="refine N new candidates first (free)")
    n.add_argument("--haiku", type=int, default=60, help="Haiku target functions in the plan")
    n.add_argument("--deepseek", type=int, default=MAX_DEEPSEEK, help="DeepSeek agents (capped at %d)" % MAX_DEEPSEEK)
    n.add_argument("--batch", type=int, default=20, help="agents spawned concurrently")
    h = sub.add_parser("harvest")
    h.add_argument("--commit", action="store_true")
    h.add_argument("--force", action="store_true", help="harvest a round again")
    sub.add_parser("status")
    a = ap.parse_args()
    {"next": cmd_next, "harvest": cmd_harvest, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()
