# The shared header library (built 2026-11-05)

`shared/include/` holds one definition per recovered game type. Before this work, matched sources
each carried their own copy (sead::SafeString alone existed in 531 files, in 24 different
spellings). A shared definition is trusted only because the matched functions built on it still
compile to the game's exact bytes.

## What it achieved

| | Before | After |
|---|---|---|
| Shared headers | 4 (202 lines) | 16 (1,580 lines) |
| Matched sources built on shared headers | 3 (+75 cp15) | 1,670 source files, 3,058 matched entries (18% of all matches) |
| Local duplicate definitions removed | – | about 2,500 (SafeString 530, static-init family 472, Vec3 451, Npc 248, ...) |
| Game helper functions declared once with their address | a handful | 93 |
| Matches lost | – | 0 (every migrated file re-verified: RESULT MATCH and IDENTITY 0 MISMATCH) |

| Header | Provides | Sources on it |
|---|---|---|
| `sead_string.h`, `sead_heap.h` | SafeString (global, `sead::` alias), BufferedSafeString, FixedSafeString<N>, NoThrow/nothrow_t, engine `operator new` (0x10BAB4) / `new[]` (0x10CEE0) | 530 / 124 |
| `static_init.h` | PtrCnt, PtrListBase/PtrList (+`Named`, `Assign` forms), Factory, Id64 | 472 |
| `vec3.h`, `sead_math.h` | Vec3 (set/setCopy, setAdd/Sub/Mul/Div/ScaleAdd, normalize...), Vec2, Vec4, Mtx33/34, Angle, SinCosSample | 451 / 62 |
| `actor.h`, `model.h` | ActorBase (0x40C) / ActorBaseExt (0x410), Npc, EnemyBase, Delegate<T>, ActorParam, Model | 302 / 2 |
| `sead_rtti.h` | TypeInfo, ObjVt<T>, RttiRoot, SEAD_RTTI_BASE | 185 |
| `flags.h`, `timer.h` | Flag32/16/8 (BitFlag* aliases), Timer | 139 / 48 |
| `statemgr.h` | StateMgrT<Owner> (exec vs execute), StateMgrBase, state-name buffer | 72 |
| `sead_container.h` | ListNode/ListImpl/OffsetList, PtrArray, Buffer<T> | 21 |
| `cp15.h`, `stdarg.h`, `albw_types.h`, `albw_common.h` | system registers, varargs, typedefs, umbrella | – |

The 93 named helpers are called from 11,120 sites in the game: 1,023 already-matched functions and
2,301 still-unmatched ones (1,656 of those are 1 KB or smaller). For those functions the helper's
name, arguments and address are now given instead of guessed.

## What it did not do

- **It matched no new function by itself.** It moved matched code onto shared types; the payoff
  is for future attempts and has not been measured yet (the validation campaign round hit the Haiku
  rate limit).
- **Five large actor constructors still do not match** with it (best: En206 114/574 words,
  TurtleMother 101/717 with the stack frame exact). Their logic is right; what remains is register
  allocation and instruction order. See `docs/HANDOVER_REGISTER_SEARCH.md` for the next step.

## Byte-level facts it established

- Several helpers really exist in two shapes in the game, distinguishable in the bytes, so the
  library carries both under distinct names: `Vec3::set` (memberwise) vs `setCopy` (`*this = o`,
  gives the split `ldm/ldr/str/strd` copy); `StateMgr::exec` (through `this`) vs `execute` (through
  a local alias); ActorBase 0x40C vs ActorBaseExt 0x410; `PtrListBase` plain / `Named` / `Assign`.
- StateMgr was a template: `changeState` exists once per actor type (0x659400, 0x65CE98, 0x65D9FC,
  0x6665A0, ...).
- `nothrow_t` must be a 1-byte type with a user-declared constructor, or armcc passes it
  differently.
- `SafeString` needs a virtual destructor, and the engine `operator new[]` must be declared, or
  armcc calls `__aeabi_vec_new_cookie` instead of the original's inline cookie code.
- Varargs need the project's own `stdarg.h` (the compiler's include tree is not in the repo):
  `va_list` is `std::__va_list` in C++, `va_start(ap, last)` is `__va_start(ap, last)`. A variadic
  member defined inside a class template makes armcc exit silently (code 5).

Details per family, including the files that could not migrate and why:
`logs/manual/LIB_*/REPORT.json` (local, gitignored) and `docs/LESSONS.md` ("Shared headers
experiment"). The five constructor attempts and their recovered types: `shared/wip/H_*/`.

## How to use and maintain it

- New sources: `#include` the header, never redefine the type locally (`docs/AGENT_BRIEF.md`,
  "Shared library"). If a function needs a form the header lacks, add it to the header as a named
  variant, with the evidence address in a comment.
- After any header edit: `uv run python tools/headercheck.py <header.h>` re-verifies every matched
  source built on it (directly or through another header). It must report 0 failing.
- To move more matched sources onto a header: `uv run python tools/headermigrate.py <Type[,Type2]>
  <header.h>` (dry run; read `logs/headermigrate/<Type>.jsonl`), then the same with `--apply`.
  Never run two `--apply` runs at once. See the tool's docstring for `--rename`, `--template`,
  `--lang`.
- Not yet migrated: definitions written as `typedef struct {...} X;` or `struct X {...} x;` (the
  harness skips them; about 80 RTTI C sources and a few flags/timer files), and sources that need a
  third form of a type (listed in the LIB reports).
