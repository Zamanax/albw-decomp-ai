---
name: decomp-campaign
description: "Default way to make progress in a session with subagents: cost-routed rounds (free harvest, cheap Haiku agents, at most 4 DeepSeek agents) driven by tools/campaign.py. Use when asked to 'continue the decomp', 'run a session', 'match more functions' with agents."
---

# Start of session (4 commands)

```
uv run python tools/campaign.py status                       # where we are
uv run python tools/campaign.py harvest --commit             # collect a round left unfinished, if any
uv run python tools/campaign.py next --refine 1000           # free work + the next paid plan
uv run python tools/mutate.py queue --register               # free: search the register/order queue
```

`next` already did the free work (famclone harvest, refine on 1,000 new candidates, a structural
score of every unmatched function's best source, the search queue) and wrote
`logs/campaign/plan.json`. `mutate.py queue` then searches `logs/campaign/search_queue.jsonl` — the
functions whose only difference is a register or an instruction position — and registers what it
matches; those never appear in the plan. Both stages are free; the plan is the only thing that costs.
Spawn and supervise it with this eval cell (Python), unchanged:

```python
import sys, importlib; sys.path.insert(0, "tools")
import campaign; importlib.reload(campaign)
campaign.run_round(agent, log)
```

`run_round` keeps a rolling window of `plan["batch"]` (20) Haiku agents, starting the next one as
soon as any finishes, and runs every DeepSeek agent alongside. Each agent has a wall-clock budget,
`TIME` in `campaign.py`: at the soft limit it gets one WRAP UP message, and at the hard limit it is
stopped. Each of its targets still missing a report then gets a timeout `REPORT.json` built from its
best logged check. A logged MATCH is still registered, and harvest re-verifies it.

Progress is visible in three places:
- the cell's live log: start, finish, wrap-up and stop events, plus a table of the running agents
  every minute (age, `*` after wrap-up, checks and best % per target, read from `fn.py`'s
  `check_log.jsonl`);
- Agent Hub (`Alt+A`) for each agent's transcript;
- `campaign.py status` from a shell.

If the cell or kernel dies mid-round, run the same cell again. Only tasks without reports start,
under fresh labels, and nothing finished is lost: every finished target already wrote its
`REPORT.json`.

Then `uv run python tools/campaign.py harvest --commit`, then `next` again. A round lasts at most
about (Haiku agents ÷ 20) × median agent time + the Haiku hard limit; the DeepSeek hard limit is
35 min.

# The mutator stage (free, before and between rounds)

`tools/mutate.py` hill-climbs the source of a function with rewrites that keep its meaning
(statement moves, `if`/`else` flips, commutative operands, named locals for sub-expressions, single-use
inlining, the library's `set`/`setCopy`, `exec`/`execute`, `PtrList` variants, integer types, flag
variants), scoring each variant with the STRUCTURE line: ~3,400 variants a minute on 16 workers, one
queued function per minute at the default 3,000-check budget.

```
uv run python tools/mutate.py queue --register     # logs/campaign/search_queue.jsonl (free, ~1 min each)
uv run python tools/mutate.py barriers --register  # the __schedule_barrier hack backlog (one-off passes)
uv run python tools/mutate.py <addr> --src FILE --budget 20000   # a family anchor by hand
uv run python tools/mutate.py tidy --register      # inline temps the search introduced but the bytes do not need
uv run python tools/structscore.py census          # per-step impact: OP=0 buckets, queue size, mutator totals
```

A match registers itself through `worklist.py register` and the next `next` clones its shape family.
Any source carrying a forbidden construct (weak, asm, volatile, `perm_t`, no-op masks, identical
if/else arms) is refused, so a refusal is a miss to park, not a match. A target the search gives up on
is marked EXHAUSTED and returns to the paid routing — that is the only way a queued function costs
money, and it happens with the mutator's measured attempt attached.

# Why it is built this way (do not undo)

- **Results live on disk.** Agents write `logs/manual/<ADDR>/REPORT.json`; harvest reads files, not
  agent messages. A dead kernel, lost handle or rate-limited agent loses nothing; a target without a
  report is simply retried next round. Never parse agent replies by hand.
- **Free before paid.** famclone (one match → its whole shape family), refine (15 flag variants) and
  the mutator (below) cost no tokens. 393 unmatched functions sit in 123 shape families; agents get
  one representative per family and famclone clones the rest.
- **Register/order differences are never paid for.** `next` scores every unmatched function's best
  source with `fn.py`'s `STRUCTURE` line and sends the ones that differ only by registers or
  instruction order to `logs/campaign/search_queue.jsonl` (one representative per shape family);
  `tools/mutate.py` searches those for free. A queued function reaches a paid tier only after the
  mutator reports it EXHAUSTED, and no member of a queued shape family is planned either.
- **Cost routing** (in `campaign.py`, constants at the top):
  - Haiku: first attempt on functions ≤ 80 words, **one target per agent**; ~$0.01-0.05/agent.
    Measured over rounds 1–14:
    - by size: 33–37% at ≤ 40 words, 18% at 41–80, 6% at 81–160;
    - by targets per agent: 27% as an agent's only target, 15% with two, 7% with three.
  - DeepSeek: **hard cap 4 per round**, one target each, only for Haiku misses or functions too big
    for Haiku whose start is ≤ 20 structural OPs away (72% at OP 6–20, 22% above 20). Ranked by
    family size × closeness. ~$0.10-0.30/agent.
  - Every target gets `logs/manual/<ADDR>/CONTEXT.md` from `next` (`tools/context.py`). It holds
    the disassembly, the target's references next to the start source's names, and related matched
    sources. Agents batch variants through `fn.py checks` and sweep flags with `fn.py flags`, since
    every round trip costs them time.
  - **Ranking:** within each tier, EV = family size × the *measured* hit rate of that tier on past
    targets of the same size and structural-OP bucket (`hit_model()`, re-learned from every round's
    plan and ledger; `next` prints the table).
  - **Reopen after a header fix:** when a shared header gains a byte-proven form, add its markers
    to `shared/reopen.json` (vtable slot, literal words, call targets, instruction encodings).
    Unmatched functions containing them ignore attempts made before `since`, take up to half of
    the Haiku slots first and half of the DeepSeek ones (`REOPEN_SHARE`), and their prompt names the form. Remove the entry
    once its functions are worked through.
  - Nobody gets the same function twice at the same tier (`logs/campaign/ledger.jsonl`, plus the
    pre-campaign `logs/manual` dirs); history and parking apply to the whole shape family.
- **A rolling window of 20 Haiku agents, with time limits.**
  - 80-100 agents at once hit the Anthropic rate limit (429) and the 100-background-job cap.
  - The old fixed batches waited for their slowest member. Agents ran from under 1 min to over
    70 min, so one slow agent held up 19 finished slots.
  - The limits come from 630 measured targets. Haiku's first match comes at a median of 0.3 min
    (max 20) after its first check; DeepSeek's at a median of 5 min (max 20). The 40-70 min tails
    produced nothing.
  - So: Haiku wraps up at 15 min and stops at 20; DeepSeek wraps up at 25 min and stops at 35.
  - A stopped target is recorded as `TIMEOUT` and moves up a tier; it is not retried at the same
    tier.
- **One brief, not a pasted context.** Agents read `docs/AGENT_BRIEF.md`; the per-task prompt is a
  few lines. Edit the brief (not prompts) when a new construct is learned.
- **Dead ends are committed.** `shared/parked.json` lists functions no tier should be paid for
  (documented open problems or steering-only matches). Add an entry with its reason when a function
  is proven blocked; remove it when a new technique applies.

# Tuning a round

`next --haiku 60 --deepseek 4 --batch 20 --refine 0`. Lower `--haiku` when the last round's Haiku
hit rate (`status`) drops below ~15%: below that, a refine batch (free) or a new family anchor is a
better use of the round. DeepSeek cannot exceed 4 (cost and rate-limit cap); `--deepseek 0` for a
Haiku-only round, e.g. when OpenRouter credits are low (a 402 error means out of credits). Time
limits are `TIME` in `campaign.py`; re-measure them from `check_log.jsonl` before changing them.

`next --queue-only` re-scores the search queue (rewriting `logs/campaign/search_queue.jsonl`) without
famclone, a new plan or moving `REPORT.json`s: use it after a mutator pass to see what is left. When
the queue is large, spend the round on `mutate.py queue` instead of agents — it is free and it
removes the near-misses the paid tiers would otherwise be paid for.

# After the round

- harvest prints per-tier outcomes, REJECTED/REFUSED lines, and commits only if `audit.py` is clean.
- A round that produced mutator matches: `mutate.py tidy --register` (drops the temps the search
  introduced but the bytes do not need) and one more `next`, so famclone collects their families.
- Record any new compiler physics a DeepSeek report explains in `docs/LESSONS.md` *and* the proven
  constructs list in `docs/AGENT_BRIEF.md` — that is how later Haiku agents get cheaper wins. When a
  mutator target fails for a structural reason (a construct choice, not an order), the same applies.
- Honesty rules (AGENTS.md) are enforced twice: by the brief and by harvest's forbidden-construct scan
  before registration. A match needing a forbidden construct is a miss; park it if documented.
