---
name: decomp-campaign
description: "Default way to make progress in a session with subagents: cost-routed rounds (free harvest, cheap Haiku agents, at most 4 DeepSeek agents) driven by tools/campaign.py. Use when asked to 'continue the decomp', 'run a session', 'match more functions' with agents."
---

# Start of session (3 commands)

```
uv run python tools/campaign.py status                       # where we are
uv run python tools/campaign.py harvest --commit             # collect a round left unfinished, if any
uv run python tools/campaign.py next --refine 1000           # free work + the next paid plan
```

`next` already did the free work (famclone harvest, refine on 1,000 new candidates) and wrote
`logs/campaign/plan.json`. Spawn it with this eval cell (Python), unchanged:

```python
import json
plan = json.load(open("logs/campaign/plan.json"))
ds = [agent(t["prompt"], label=t["name"], model=t["model"]) for t in plan["tasks"] if t["tier"] == "deepseek"]
hk = [t for t in plan["tasks"] if t["tier"] == "haiku"]
B = plan["batch"]
for i in range(0, len(hk), B):
    wait([agent(t["prompt"], label=t["name"], model=t["model"]) for t in hk[i:i + B]], raise_errors=False)
try:
    wait(ds, raise_errors=False)
except RuntimeError:
    pass   # DeepSeek finished before the last Haiku batch: results expired from the bridge, but are on disk
```

If the cell or kernel dies mid-round, do nothing special: every finished target already wrote its
`REPORT.json`. Run harvest; unreported targets are re-planned by the next `next`.

Then `uv run python tools/campaign.py harvest --commit`, then `next` again. One round ≈ 15-25 min.

# Why it is built this way (do not undo)

- **Results live on disk.** Agents write `logs/manual/<ADDR>/REPORT.json`; harvest reads files, not
  agent messages. A dead kernel, lost handle or rate-limited agent loses nothing; a target without a
  report is simply retried next round. Never parse agent replies by hand.
- **Free before paid.** famclone (one match → its whole shape family) and refine (15 flag variants)
  cost no tokens. 393 unmatched functions sit in 123 shape families; agents get one representative
  per family and famclone clones the rest.
- **Cost routing** (in `campaign.py`, constants at the top):
  - Haiku: first attempt on functions ≤ 160 words; ~$0.01-0.05/agent, ~35-50% hit rate on the
    closest near-misses, falling off fast further down the list.
  - DeepSeek: **hard cap 4 per round**, one target each, only for Haiku misses or functions too big
    for Haiku, ranked by family size × closeness. ~$0.10-0.30/agent, ~70-80% on Haiku misses.
  - Nobody gets the same function twice at the same tier (`logs/campaign/ledger.jsonl`, plus the
    pre-campaign `logs/manual` dirs); history and parking apply to the whole shape family.
- **Batches of 20 Haiku agents.** 80-100 at once hit the Anthropic rate limit (429) and the
  100-background-job cap. DeepSeek runs in parallel with the Haiku batches (it is slower).
- **One brief, not a pasted context.** Agents read `docs/AGENT_BRIEF.md`; the per-task prompt is a
  few lines. Edit the brief (not prompts) when a new construct is learned.
- **Dead ends are committed.** `shared/parked.json` lists functions no tier should be paid for
  (documented open problems or steering-only matches). Add an entry with its reason when a function
  is proven blocked; remove it when a new technique applies.

# Tuning a round

`next --haiku 60 --deepseek 4 --batch 20 --refine 0`. Lower `--haiku` when the last round's Haiku
hit rate (`status`) drops below ~15%: below that, a refine batch (free) or a new family anchor is a
better use of the round. DeepSeek cannot exceed 4 (cost and rate-limit cap); `--deepseek 0` for a
Haiku-only round, e.g. when OpenRouter credits are low (a 402 error means out of credits).

# After the round

- harvest prints per-tier outcomes, REJECTED/REFUSED lines, and commits only if `audit.py` is clean.
- Record any new compiler physics a DeepSeek report explains in `docs/LESSONS.md` *and* the proven
  constructs list in `docs/AGENT_BRIEF.md` — that is how later Haiku agents get cheaper wins.
- Honesty rules (AGENTS.md) are enforced twice: by the brief and by harvest's forbidden-construct scan
  before registration. A match needing a forbidden construct is a miss; park it if documented.
