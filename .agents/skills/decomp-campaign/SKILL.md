---
name: decomp-campaign
description: "Default way to make progress in a session with subagents: one eval cell (campaign.run_loop) chains cost-routed rounds with no model turn between them - a one-turn Haiku screen first, the full Haiku agent only inside the screen's gate, DeepSeek off by default. Use when asked to 'continue the decomp', 'run a session', 'match more functions' with agents."
---

# Start of session (one command, one cell)

```
uv run python tools/campaign.py status       # where we are
```

Then this eval cell (Python, cell `timeout: 0`), unchanged:

```python
import sys, importlib; sys.path.insert(0, "tools")
import campaign; importlib.reload(campaign)
campaign.run_loop(agent, log)
```

That is the whole session. `run_loop` repeats, with no model turn in between:

1. `campaign.py harvest --commit` - collects the previous round (or one left unfinished), registers
   and commits.
2. `campaign.py next --screen 300 --haiku 80 --deepseek 0` - free work (famclone, structural scores,
   the search queue) and the next plan.
3. `run_round` - spawns and supervises the plan, while `mutate.py queue --register --budget 1000`
   searches the register/order queue alongside.

It ends when the plan is empty (then `mutate.py tidy --register` and a last harvest), or stops early
when more than half of a round's targets got no report. **Do not supervise it turn by turn and do not
run the steps by hand between rounds.** The Opus session that used to do that cost more than all
Haiku agents together ($65.8 against $36.9 over rounds 1-22) and shares their Anthropic cap. When the
cell returns, read its log and report the totals.

# The tiers (cheapest first; a function climbs only when the cheaper tier says it is worth it)

| tier | what it is | cost / time | who gets it |
|---|---|---|---|
| free | famclone, refine's flag variants, `mutate.py` on `OP=0`/order-only sources | CPU | everything, before and between rounds |
| `screen` | ONE Haiku turn, no tools: the prompt inlines the brief's rules, `CONTEXT.md` and the start source; the agent writes 4 candidates to `logs/manual/<ADDR>/screen/`; `run_round` compiles them (default flags, then the flag sweep on the best two) and writes `REPORT.json` | ~$0.0075, ~25 s | every function ≤ 80 words no tier has tried |
| `haiku` | the full agent (reads `docs/AGENT_BRIEF.md`, runs its own checks) starting from the screen's best candidate | ~$0.02-0.04, ~2 min | screened functions inside the gate `SCREEN_PASS`: best source at `OP ≤ 2` for ≤ 40 words, `OP ≤ 5` for 41-80 |
| `deepseek` | one agent per target, hard cap 4 per round | ~$0.10-0.30, 4-8 min | off by default; Haiku misses and functions > 80 words whose start is ≤ 20 OPs away |

A clean screen match (bytes, `IDENTITY 0 MISMATCH`, no forbidden construct) is registered by harvest
like any agent match. A screen's best candidate at `OP=0` goes to the mutator queue first and reaches
the Haiku agent only after the mutator reports it EXHAUSTED.

# Watching it

- the cell's live log: per round the harvest and plan summaries, one line per compiled batch of
  screens (`screens 53/120: +2 compiled (MATCH 1, MISS 1)`), one line per finished agent, a table of
  the running agents every minute, the mutator's totals;
- `uv run python tools/campaign.py status` from a shell (hit rate per tier, the live plan);
- Agent Hub (`Alt+A`) for a transcript.

Measured: a round of 120 screens + 13 agents ran 4 min, 6.5 min with its harvest and plan.

# When it stops or dies

- `STOP: N of M targets got no report` - the agents are failing: an Anthropic `429` (the weekly cap
  answers with a retry-after of days) or an OpenRouter `402` (credits). Nothing is lost and nothing is
  recorded as tried: run the same cell again later.
- The cell or kernel dies mid-round: run the same cell again. The harvest takes what was reported,
  screens whose candidates are on disk are compiled instead of re-run, and everything else is
  planned again.
- `docs/AGENT_BRIEF.md has no '## …' section` from `next`: the screen prompt inlines the sections
  named in `BRIEF_SECTIONS`; a renamed heading must be renamed there too.

# Tuning

`campaign.run_loop(agent, log, rounds=0, screen=300, haiku=80, deepseek=0, haiku_rest=False)`

Spend in this order (estimates from the pilot, `docs/LESSONS.md` "One-turn screen"; `status` has the
live rates):

| step | setting | functions | est. matches | $/match |
|---|---|---|---|---|
| screen + gated agent | the defaults | 3,358 screens, ~700 agents | ~365 | ~$0.13 |
| the rest ≤ 40 words | `haiku_rest=True`, once the defaults leave nothing to plan | ~1,070 agents | ~140 | ~$0.28 |
| the rest at 41-80 words | not offered: ~5% for the agent | ~1,590 | ~85 | ~$0.72 |

- `rounds=N` stops after N rounds (a bounded session).
- `deepseek=4` adds the DeepSeek tier. It costs about the same per match as Haiku at 41-80 words
  ($0.23 against $0.30) and is several times slower, so it is for Haiku near-misses only.
- One round by hand: `campaign.py next …`, then `campaign.run_round(agent, log)` in the cell, then
  `campaign.py harvest --commit`. `next --queue-only` re-scores the search queue without a plan.
- The gate: `SCREEN_PASS` in `campaign.py`. Each screen's ledger row carries `op` (its best
  candidate's structural OP), so the gate can be re-measured by joining those rows with the later
  `haiku` rows of the same address. Functions outside the gate only reach the agent under
  `haiku_rest`, which is therefore also the way to test a wider gate.
- Time limits are `TIME` in `campaign.py` (screen 4 min hard, Haiku 15/20, DeepSeek 25/35);
  re-measure from `check_log.jsonl` before changing them.

# The mutator stage (free)

`tools/mutate.py` hill-climbs a source with rewrites that keep its meaning (statement moves,
`if`/`else` flips, commutative operands, named locals, single-use inlining, the library's
`set`/`setCopy`, `exec`/`execute`, `PtrList` variants, integer types, flag variants), scored by the
STRUCTURE line. The loop runs it at 1,000 checks per function (42 of its 48 matches needed no more;
~20 s each). By hand:

```
uv run python tools/mutate.py queue --register             # logs/campaign/search_queue.jsonl, 3,000 checks each
uv run python tools/mutate.py queue --register --again     # also the ones the loop gave up on at 1,000
uv run python tools/mutate.py <addr> --src FILE --budget 20000   # a family anchor by hand
uv run python tools/mutate.py barriers --register          # the __schedule_barrier hack backlog
uv run python tools/mutate.py tidy --register              # inline temps the search introduced but the bytes do not need
uv run python tools/structscore.py census                  # OP=0 buckets, queue size, mutator totals
```

A match registers itself through `worklist.py register` and the next `next` clones its shape family.
A source carrying a forbidden construct is refused: a refusal is a miss to park, not a match.

# Why it is built this way (do not undo)

- **Results live on disk.** Agents write `logs/manual/<ADDR>/REPORT.json` (a screen:
  `screen/s1..s4.{c,cpp}`, and `run_round` writes the report); harvest reads files, not agent
  messages. A dead kernel, lost handle or rate-limited agent loses nothing. Never parse agent replies.
- **Free before paid.** famclone (one match → its whole shape family), refine and the mutator cost no
  tokens. Agents get one representative per shape family.
- **One cheap turn decides whether the agent is worth its price.** Measured on 80 past Haiku targets:
  one tool-less turn matches ~3% outright, three such turns 11% against the agent's 18% at the same
  cost - so the turn does not replace the agent. But where its best candidate is ≤ 2 OPs away the
  agent matched 44-67%, and ~10% everywhere else. The gate keeps 65% of the agent's matches at ≤ 40
  words for 29% of the agent runs.
- **Screen candidates live in `screen/`.** `attempted()` reads a source directly under
  `logs/manual/<ADDR>/` as a Haiku agent's attempt; a screen must not use up that turn.
- **The screen prompt is self-contained and generated.** It inlines the brief's sections, so edit
  the brief (not prompts) when a construct is learned; both tiers pick it up.
- **No model in the loop.** Every step between rounds is a tool with a `NEXT` line; `run_loop` calls
  them. A model turn there buys nothing and was the largest cost line.
- **Size is the signal.** Haiku agent by planned size: 27% at ≤ 20 words, 33% at 21-40, 13% at 41-80,
  5% above 80. Start-source quality barely predicts it; the screen's OP does.
- **A rolling window of 20 Anthropic agents** (screens and Haiku agents share it), DeepSeek alongside.
  80-100 at once hit the 429 and the 100-background-job cap. Haiku matches come within 2 min of the
  first check; the limits only cut the tail.
- **Nobody gets the same function twice at the same tier** (`logs/campaign/ledger.jsonl`, plus the
  pre-campaign `logs/manual` dirs); history and parking apply to the whole shape family.
- **Reopen after a header fix.** When a shared header gains a byte-proven form, add its markers to
  `shared/reopen.json`. Unmatched functions containing them ignore attempts made before `since` -
  they are screened again - and their prompt names the form. Reopened retries at 41-80 words convert
  at 5%: `REOPEN_SHARE` caps them. Remove the entry once its functions are worked through.
- **Dead ends are committed.** `shared/parked.json` lists functions no tier should be paid for. Add
  an entry with its reason when a function is proven blocked; remove it when a new technique applies.
- **Large functions are not this skill's job.** Above 80 words the agents have matched ~50 functions
  from scratch; the other 1,000+ large matches are shape families and the `fam_sti` generator.

# After the session

- harvest prints per-tier outcomes, REJECTED/REFUSED lines, and commits only if `audit.py` is clean.
- Record any new compiler physics an agent report explains in `docs/LESSONS.md` *and* the proven
  constructs list in `docs/AGENT_BRIEF.md` - the screen and the agents both read that list.
- Honesty rules (AGENTS.md) are enforced three times: by the brief, by the screen's and harvest's
  forbidden-construct scan, and by `worklist.py register`. A match needing a forbidden construct is
  a miss; park it if documented.
