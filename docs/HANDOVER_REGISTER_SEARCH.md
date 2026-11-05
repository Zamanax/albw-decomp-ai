# Handover: register allocation and instruction order (2026-11-05)

Goal of the next session: stop paying language-model agents for differences that are only
register choice or instruction order, and let the machine search for them instead. Three steps,
in this order:

1. **Structural score** (idea 3): tell "wrong instruction" apart from "right instruction, other
   register" and "right instruction, other position".
2. **Routing** (idea 1): functions whose only differences are registers/order never go to a paid
   agent; they go to a search queue.
3. **Automatic mutator** (idea 2): a free, parallel search that rewrites the source in meaning-
   preserving ways and keeps whatever scores better.

Do step 1 before step 2: routing is only as good as the classification it routes on (see below).

## State at handover

- `master` includes the shared header library (`docs/SHARED_LIBRARY.md`): 16 headers, 1,670
  matched source files on them, 0 matches lost. `functions.json`: 17,079 honest, 129 hack.
- Campaign: Haiku 82/325 matches (25%), DeepSeek 41/66 (62%). Round 7 was planned but every Haiku
  agent hit a 429 rate limit (retry window ~3 h after 2026-11-05 11:45); no reports were written,
  so the next `campaign.py next` simply re-plans those targets. OpenRouter credits were topped up.
- Still to do from the library work: one validation round to measure whether the library raises
  the Haiku hit rate (baseline 25%):
  `uv run python tools/campaign.py next --haiku 20 --deepseek 0 --refine 0`, spawn, harvest.

## Why the current classification is not good enough (measured at handover)

`tools/sweep.py` `classify()` (lines ~84-127; refine.py uses it too) compares the target and our
build **row by row**. Anything that moves an instruction to another position, or adds one,
misaligns every later row and counts as an OP (wrong instruction) difference. Measured:

| Source | Agent's description | Current classifier |
|---|---|---|
| 0060BE24 best (`shared/wip/P4_fam_0060BE24/best.cpp`) | 13 words, register rotation plus one swapped pair, all instructions right | OP=14 REG=11 |
| 0060C038 best (`shared/wip/P5_fam_0060C038/best.cpp`) | one missing `mov r1,r0`, everything else identical | 6/22 words, OP=2 (similarity 93%) |
| En206 best (`shared/wip/H_00206FBC/best.cpp`) | logic right, stack frame and allocation differ | 114/574 words, OP=562 |

Across all 255 unmatched agent best sources under `logs/manual/*/REPORT.json`, only **3** classify
as OP=0 (003CBE60, 00542AE4, 001112A8) and 13 as OP 1-2. Across refine's 7,889 best sources only
1 is OP=0. Routing on today's numbers would send almost nothing to the search. Also note the word
score itself (`RESULT: ... N/total words`) is positional for the same reason, which is why
0060C038's best reads 6/22 while it is one instruction away.

## Step 1: structural score (idea 3)

Where:
- `tools/fn.py` `cmd_check` (line ~449). It already aligns the two instruction streams for the
  `similarity` figure (comment "alignment-based similarity", line ~552) and prints
  `RESULT:` at line ~588.
- `tools/sweep.py` `classify()`, `canon()` (register names → `R`), `REGTOK`.

What to build:
- Align target and ours on the canonical (register-blind) instruction text with an LCS / diff
  alignment, not by row index. Then count:
  - `OP`: instructions present on one side only, or aligned but different after canonicalisation;
  - `REG`: aligned, same canonical text, different registers;
  - `MOVED`: identical (canonical) instructions that exist on both sides but at different
    positions (detect by matching the unaligned leftovers as a multiset).
- Print it as an extra line from `fn.py check`, e.g.
  `STRUCTURE: OP=1 REG=0 MOVED=0 aligned 21/22`. Keep the `RESULT:` and `IDENTITY:` lines exactly
  as they are: worklist.py, refine.py, campaign.py, headermigrate.py, headercheck.py and dehack.py
  parse them.
- Make `sweep.classify()` use the new alignment (refine and sweep then improve automatically).
  Literal-pool words and relocated words must keep the existing masking rules.

Acceptance:
- Every matched function: OP=0 REG=0 MOVED=0 (spot-check 100 random honest entries).
- 0060C038 best: OP=1 (the missing `mov r1,r0`), REG and MOVED near 0.
- 0060BE24 best: OP at most 2 (the two swapped arg-setup instructions may show as MOVED instead),
  the rest REG.
- Re-run the 255-file measurement above and record the new OP=0 / OP 1-2 counts in LESSONS.

## Step 2: routing (idea 1)

Where: `tools/campaign.py`
- `near_misses()` (line ~110) reads only refine's `logs/refine/<addr>/state.json` (`n_op`).
- `cmd_next` ranks by `ev = fanout * (1 - n_op/total)` (line ~213) and assigns Haiku/DeepSeek.

What to build:
- For each candidate, take the best of refine's source and the agents' best source
  (`logs/manual/<ADDR>/REPORT.json` `file` + `flags`), scored with step 1's structure.
- If OP == 0 (only REG/MOVED left), or OP is small and every OP is an order-only effect, put it in a
  search queue (e.g. `logs/campaign/search_queue.jsonl` with addr, source path, flags, structure)
  instead of a paid tier. Print the queue size in `next`.
- Never assign a paid agent to a queued function. Paid tiers keep functions with real OP
  differences (wrong logic, missing calls, constants).

Acceptance: `campaign.py next` prints e.g. `search queue: N functions (OP=0: a, OP<=2 order-only: b)`
and no plan task has a queued address.

## Step 3: automatic mutator (idea 2)

Existing pieces:
- `tools/permuter.py`: `check_one(workdir, src, addr, flags, sym)` compiles+checks one variant in a
  killable subprocess; the tool itself expands a hand-written TEMPLATE/GRID (cartesian product).
- `tools/sweep.py`: same with coupled GROUPS and BODY statement permutations, plus the classifier.
- `tools/refine.py`: has an ORDER wave (statement permutations) for REG/PERM bests.
Today every variant set is written by hand or by an agent. The new tool must invent them.

What to build (`tools/mutate.py` or an extension of sweep.py):
- Input: a function address, a source file, flags. Output: `logs/mutate/<ADDR>/` with the best
  source so far, a score log, and the matching source if found.
- Mutations (all must keep the meaning; apply 1-3 at random per variant):
  reorder two adjacent independent statements or declarations; introduce a named local for a
  sub-expression that is then used (`T x = expr; ... x ...`), or inline an existing single-use
  local; swap operands of commutative operators (`+ * & | ^ == !=`) and of `&&`/`||` when both sides
  are side-effect free; rewrite `p->a.b` through a pointer or reference local; switch between the
  library's named helper variants (`set`/`setCopy`, `exec`/`execute`, `PtrList`/`Named`/`Assign`);
  toggle the flag variants refine already knows (-O2, -O3 without -Otime, -Ono_tailcall, fpic,
  Cortex-A9).
- Search: hill climbing with random restarts on step 1's score (fewest OP, then REG+MOVED), 16
  parallel workers (`--jobs 16` is safe natively; ~0.1-0.2 s per check, so roughly 5,000 variants a
  minute).
- Honesty: never generate the AGENTS.md forbidden constructs. A new local must be genuinely used
  (an assigned-and-used temp is ordinary C; an unused or `volatile` one is a forbidden dummy). Run
  the result through `worklist.py register`, which re-verifies and applies the construct gates.
- Language: sources are mostly C++. The upstream decomp-permuter (pycparser) only handles C, so
  either mutate at the token/statement level on the function body, or use a C++ parser; decide
  early.

Pilot targets, in order (all tracked in `shared/wip/` unless noted):

| Target | Source | Why |
|---|---|---|
| 0060BE24 family, 51 functions | `shared/wip/P4_fam_0060BE24/best.cpp` (107/120) | Register rotation only (owner base r5 vs r7), plus a swapped arg-setup pair at 0x78/0x7c and `sub r1,r2,r1` vs `sub r1,r1,r2`. One match gives all 51 via `tools/famclone.py`. Parked in `shared/parked.json`: unpark on success. |
| 64 `__schedule_barrier` hacks | `shared/wip/P2_schedule_barrier/remaining_final.json`, `classification.json` | Pure load/store order swaps; an honest version de-hacks them. |
| 003CBE60, 00542AE4, 001112A8 | `logs/manual/<ADDR>/` (local only) | The only OP=0 agent near-misses today. |
| 0060C038 family, 49 functions | `shared/wip/P5_fam_0060C038/best.cpp` | One missing `mov r1,r0`: an OP, so less likely for a pure mutator; LESSONS explains the mechanism. |
| En206 00206FBC | `shared/wip/H_00206FBC/best.cpp` (114/574) | Stretch goal: large constructor whose logic is right. |

Acceptance: at least one pilot target matched honestly by the mutator, registered through
`worklist.py register`; or a measured report (variants tried, best structure reached) per target.

## Practical notes

- Run every tool as `uv run python tools/<tool>.py ...` from the repo root.
- Windows: never pipe `fn.py` output into `head` (OSError on the closed pipe); write to a file.
- argparse: a value starting with `-` needs the `--opt=value` form (`--rename=->exec\(\)=...`).
- One `headermigrate.py --apply` at a time; dry runs may run in parallel.
- Model costs: Haiku ~$0.01-0.05 per agent, DeepSeek ~$0.10-0.40; a 402 from OpenRouter means its
  credits are out, a 429 from Anthropic means the rate limit (wait, do not retry in a loop).
- Before committing index changes: `uv run python tools/audit.py` must be CLEAN.

## Prompt to start the new session

> Read `docs/HANDOVER_REGISTER_SEARCH.md`, then `AGENTS.md`. Implement step 1 (structural score in
> `tools/fn.py` / `tools/sweep.py`) and verify it against the acceptance list, then step 2 (routing
> in `tools/campaign.py`), then step 3 (an automatic source mutator) and run it on the pilot targets
> starting with the 0060BE24 family. Record measured results in `docs/LESSONS.md`.
