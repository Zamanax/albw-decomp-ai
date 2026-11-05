# Agent brief (read fully before starting)

You are a subagent of a matching-decompilation campaign for The Legend of Zelda: A Link Between
Worlds (3DS, USA). For each target address you are given, write C or C++ that compiles with the
original compiler (armcc 4.1 build 1049) to **exactly** the game's bytes. Your task message gives the
targets, your check budget and where to start.

## Tools (repo root `C:\Dev\clones\albw-decomp-ai`; run every command from there)

- `uv run python tools/fn.py show 0xADDR` — annotated disassembly (calls and globals named).
- `uv run python tools/fn.py xref 0xADDR` — callers / references.
- `uv run python tools/fn.py check <file> 0xADDR --cc 4.1/b1049 --flags "<flags>"` — the oracle
  (~0.1 s, parallel-safe). `.c` compiles as C99, `.cpp` as C++. Never pipe it into `head`
  (Windows raises OSError on the closed pipe); redirect to a file in your work dir instead.
  Evaluate **every** candidate with it, never with a private compile/compare script: each check is
  logged to `check_log.jsonl`, which is how the operator watches your progress live, and how your
  best attempt is collected if you are stopped.
- Default flags: `--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections`.
- Starting point: `logs/refine/<ADDR>/best.c` (its real language is `ext` in
  `logs/refine/<ADDR>/state.json`; `origin` names the matched twin it came from). The twin is often
  a *different* function of similar shape: if callees, offsets, sizes or constants don't line up with
  `fn.py show`, write the function from the disassembly instead.
- References: matched sources in `src/work8/auto/` (grep them for the callee or global you see),
  `shared/include/` (the shared library, below), `docs/LESSONS.md`.

## Shared library (`shared/include/`, already on the include path)

1,654 matched sources build on these; each is the form that those functions' bytes prove. **Use
them, never redefine the type locally.** A local copy is what makes an otherwise right function
differ in register allocation or store order.

| Header | Provides |
|---|---|
| `sead_string.h`, `sead_heap.h` | `SafeString` (global, `sead::` alias), `BufferedSafeString`, `FixedSafeString<N>`, `NoThrow`/`nothrow_t`, engine `operator new`/`new[]` (Heap-like tag, 0x10BAB4/0x10CEE0) |
| `vec3.h`, `sead_math.h` | `Vec3` (both copy helpers: `set` memberwise, `setCopy` = `*this = o`), `Vec2`, `Vec4`, `Mtx33/34`, `Angle`, `SinCosSample`, `sinCos` |
| `statemgr.h`, `actor.h`, `model.h` | `StateMgrT<Owner>` (`exec` vs `execute` forms, `StateMgrBase`), `ActorBase`/`ActorBaseExt`/`ActorBaseA/B`, `Npc`, `EnemyBase`, `Delegate<T>`, `ActorParam`, `Model` |
| `static_init.h`, `sead_container.h` | `PtrCnt`/`PtrList*`/`Factory` (+ `…Named`, `…Assign` forms), `Id64`, `ListNode`/`ListImpl`, `PtrArray`, `Buffer<T>` |
| `flags.h`, `timer.h` | `Flag32`/`Flag16`/`Flag8` (`BitFlag*` aliases), `Timer` |
| `sead_rtti.h` | `TypeInfo`, `ObjVt<T>`, `RttiRoot`, `SEAD_RTTI_BASE` |
| `cp15.h`, `stdarg.h`, `albw_types.h` | system registers, varargs for `...` functions, integer/float typedefs |

If the interaction is different from the library form (the same helper exists in two shapes in the
game), say which form your function needs in the report instead of forking the type locally.

## Done means — both lines, verbatim from `fn.py check`

- `RESULT: MATCH  N/N words`
- `IDENTITY: … 0 MISMATCH` — name every extern after the address it really targets:
  `func_XXXXXXXX` (8 uppercase hex digits), `data_XXXXXXXX` / `g_XXXXXXXX`, `ro_XXXXXXXX`.
  A source calling the wrong function can byte-match; IDENTITY catches it.

## Honesty (hard rules — a match that needs one of these is worthless)

Forbidden: `__attribute__((weak))` / `__weak`, `__schedule_barrier()`, inline `asm`/`__asm`, dummy or
`volatile` locals, out-of-bounds dummy arrays, `& 0xffffffff`, if/else or `?:` whose arms yield the
same value (`x ? x : 0`), `do { } while (0)` wrappers, `perm_t`, dead guards/branches that only steer
the compiler, semantically wrong code. Remove any of these if the start source has them.
Prefer an honest miss. Never claim a match you did not see printed.

## Order of work (cheapest first)

1. `fn.py show`, then check the start source with the default flags. Diff every callee, offset,
   allocation size, immediate and literal-pool value against the disassembly — most wins are a
   wrong constant/offset/callee or a missing/extra call.
2. **Flag sweep** on your best source (one check each): default, `-O2`, `-O2 -Otime`, `-O3` (no
   `-Otime`), `--apcs=/fpic` at each level, `--cpu=Cortex-A9`. Some functions were built with other
   flags; report the flags that match.
3. Source-shape work, using the proven constructs below before inventing new ones.

## Proven constructs

- Last word `mov r0, r0` (often after `pop {…,lr}`): linker-NOPed tail call to the function that
  starts right after this one — end the source by calling it with the right args in r0-r3.
- Original `bl X; pop {…,pc}` but armcc emits a tail `b X`: add `-Ono_tailcall` before
  `--split_sections` (keeps everything else identical), or `--apcs=/fpic` (never tail-calls).
  If another call in the same function must stay a tail call, declare only X with
  `extern "C" void func_XXXXXXXX(...) __attribute__((notailcall));` — allowed only when
  `uv run python tools/notailcall.py check <your file>` prints `ok` (X never tail-called anywhere).
- `mrc/mcr p15` (thread pointer, DSB/DMB) or `vmrs/vmsr fpscr`: `#include "cp15.h"` and read/write
  `tls_tp` / `dsb_tp` / `dmb_tp` / `fpscr_reg`. Never write `__asm` yourself.
- Value/constant in the wrong register: pass it through an inlined helper's *parameter*, a
  pointer/reference local (`T* s = &p->m; s->f();`), or a named local right before the call.
  Parameterised `inline`/member helpers are inlined late (after constant promotion), parameterless
  ones early — use a member helper with a parameter to keep two equal constants in different regs.
- VFP registers off by one (s3 vs s2…): combine a named float local for a loaded field
  (`f32 y = g->pos->y;`) with a pointer local for the compared struct (`Vec3* p = &o->pos;`);
  00521100 needed both — either alone stays at 17/19.
- Dead count load before a data-pointer load: inlined bounds-checked accessor
  `T& at(u32 i){ if (i < n) return d[i]; return d[0]; }` used at a constant index.
- Stored value re-read through the same slot (`u32& s = c->v; s = x; u32 b = s;`) reproduces
  load orders and `vmov` core/VFP transfers.
- Bool normalisation `u32 b = v; if (b) b = 1;` gives `movne r1,#1; cmp r1,#0`.
- Two `ldr` (one with writeback `ldr r3,[r0,#0x78]!`) where you emit `ldrd`: the field is an
  unaligned 64-bit value — read it through a `__packed u64* q = &x->v;` local (00429F14). A u64
  inequality tail `eor`/`orrs` with swapped pair regs: `u64 d = a ^ b; return d ? 1 : 0;`.
- Instruction shapes plateau far below a twin's match: sweep `-O3` without `-Otime` and `-O2`
  before reshaping (003AA984 family plateaued at 27/44 with -Otime, exact without).
- Float field compared against two ints (`vcvt` then `cmp`/`cmpne` with `vmovne r1,s0`): cast at
  each comparison, `(s32)o->v == 1 || (s32)o->v == 3`, not a cached int local (003327FC).
- Virtual call whose argument load is scheduled before the object/vtable load in the original: write
  the dispatch as a function-pointer local, `void (*fp)(T*,s32,s32) = *(void(**)(T*,s32,s32))
  ((char*)(*(void**)q) + 0xac); fp(q, q->m854, -1);` (0060BD64 family, 51 functions).
- Two adjacent stores in the wrong order: struct copy `T tmp = r; tmp.m = 1; r = tmp;` (001D3DBC) or a
  pointer local per stored field (002D455C).
- `mov r0, r0` in the *middle* of a body (r0 still holds `this`): a call to a 4-byte `bx lr` no-op
  (e.g. `func_001E6CE8(p)`, found in many vtables) that armlink NOPed — write the call (003B39BC).
- 12-byte struct copied as a 2-word `ldm` + separate `ldr`/`str` where you emit one 3-word `ldm`:
  copy through a pointer local, `Vec3* q = &p->v; Vec3 t = *q;` (002A0714).
- Field loaded into r0 where the original loads into another reg and masks into a fresh one: read
  the field twice (`if (s->m == 0) …; u32 c = (u8)s->m;`) so the base stays live (00542AE4).
- Families with matched examples in `src/work8/auto/`: static-TypeInfo dynamic_cast
  (`func_0022FA4C.c`, `func_00125FE4.c` — `dynCast(a) = isDerived(a) ? a : 0`), sead RTTI root
  (`func_0051E33C.cpp`), singleton getters (`func_0010D5C8.cpp`), state-machine `execute()`
  (`func_0017A6D8.cpp`, `func_00311DE0.cpp`), static initializers (`func_005B8944.cpp`), destructor
  chains (`func_0024673C.cpp`, `func_00373A60.cpp`).

## Boundaries

- Write files ONLY under `logs/manual/<ADDR>/` (8 hex digits, no `0x`) — never in the repo root or
  anywhere else, not even scratch scripts.
- Never edit `functions.json`, `src/`, `tools/`, `shared/` or docs; never run git, `worklist.py`,
  `refine.py` or `campaign.py`.
- Respect the check budget and the time budget in your task message. A `WRAP UP` message means:
  stop exploring, write every target's `REPORT.json` now, and finish. At the hard time limit you are
  stopped; a target without a report is then recorded as a timeout from your best logged check.

## Reporting (mandatory — this is how your work is collected)

For **each** target, write `logs/manual/<ADDR>/REPORT.json`:

```json
{"addr": "0051E33C", "status": "MATCH", "file": "logs/manual/0051E33C/final.cpp",
 "flags": "--cpu=MPCore --fpmode=fast --apcs=/interwork -O3 -Otime --split_sections",
 "words": "23/23", "note": "one line: the fix, or for a MISS what still differs"}
```

`status` is `MATCH` only if you saw both lines above printed for that exact file and flags;
otherwise `MISS` with your best `words`. Then reply with a single line: `DONE <n> MATCH, <m> MISS`.
