// Static-initialisation scaffolding: the little sead-side types that static-initialiser functions
// construct for the game's global objects.
//
// One definition for every matched source (tools/headermigrate.py measures how many independently
// matched functions accept it unchanged). The initialisation order of a unit's globals follows
// their definition order in the source; classes with static members (see func_005B8944) let a
// unit order .bss separately from the order the constructors run, which is why sources declare
// `struct Res { static PtrList<5> list; static Factory factory; ... };` and define the members in
// the required order.
//
// Init-order evidence: 0x005B8944 (IdPair/Pair, then SafeString table, then PtrList<5> then the
// Factory whose payload follows the float vector), 0x0059C094, 0x005BDEA8, 0x005E2ED4, 0x005CE944
// ("declare the globals in address order; the pointer-holding struct last").
//
// The types are at global scope because every matched source that defines them does so at global
// scope (the original's `sead::` namespace is not reconstructed here; see sead_rtti.h/sead_string.h
// for the namespaced stand-ins).

#ifndef ALBW_STATIC_INIT_H
#define ALBW_STATIC_INIT_H

#include "albw_types.h"

typedef long long s64;  // albw_types.h carries u64 only; every source spells s64 `long long`

// The string type a Factory constructor's `const SafeString&` arguments convert to (implicitly,
// from a `const char*`). Forward-declared, never defined here: each unit brings its own definition
// (a `{vptr; const char*}` class with an empty inline destructor), and using that exact type keeps
// the temporary's construction identical. See sead_string.h for the namespaced reconstruction.
struct SafeString;

// sead::Id (the "-1 identifier" sentinel). Only ever used as `Id64().v` in an initialiser.
struct Id64 {
    s64 v;
    Id64() : v(-1) {}
};

// sead's intrusive pointer list, as used by the resource/Factory registration tables.
// PtrCnt = the count/limit pair; PtrListBase = the pointer to the backing array; PtrList<N> = the
// inline array (the only form in the corpus, 447/447 sources).
struct PtrCnt {
    int num, max;
    PtrCnt(int n) : num(0), max(n) {}
};

struct PtrListBase : PtrCnt {
    void** ptr;
    // The buffer argument is stored as-is; a null one leaves the previous (null) pointer.
    PtrListBase(int n, void* b) : PtrCnt(n), ptr(0) { if (b) ptr = (void**)b; }
};

template <int N>
struct PtrList : PtrListBase {
    void* buffer[N];
    PtrList() : PtrListBase(N, buffer) {}
};

// Second inlining form of the same two constructors: the buffer argument passes through a named
// local (`void** t = static_cast<void**>(b); ptr = t;`) before the store. Same object layout; only
// the register allocation of the inlined body differs. 0x005BDEA8, 0x0059C094 and 0x005E2ED4
// matched with it (the seven-word body keeps `adds`/`strne` apart where the form above fuses);
// rename PtrListBase/PtrList to these in those units.
struct PtrListBaseNamed : PtrCnt {
    void** ptr;
    PtrListBaseNamed(int n, void* b) : PtrCnt(n), ptr(0) {
        if (b) {
            void** t = static_cast<void**>(b);
            ptr = t;
        }
    }
};

template <int N>
struct PtrListNamed : PtrListBaseNamed {
    void* buffer[N];
    PtrListNamed() : PtrListBaseNamed(N, buffer) {}
};

// Third form (0x00465FE0, an Obj constructor holding `PtrList<0x40> mList`): the count/limit pair
// has no constructor, so the derived constructor assigns all three fields and armcc merges
// (num, max) into one STRD instead of (max, ptr). Same layout.
struct PtrCntBare {
    int num, max;
};

struct PtrListBaseAssign : PtrCntBare {
    void** ptr;
    PtrListBaseAssign(int n, void* b) { num = 0; max = n; ptr = 0; if (b) ptr = (void**)b; }
};

template <int N>
struct PtrListAssign : PtrListBaseAssign {
    void* buffer[N];
    PtrListAssign() : PtrListBaseAssign(N, buffer) {}
};

typedef void* (*CreateFn)();

// sead::Factory: an opaque 0x248-byte block; both the constructor and the destructor are real
// game functions (out of line here, as in every matched source).
//
// The fourth parameter is the list the factory registers into. It is typed `PtrCnt*` rather than
// `PtrListBase*` because the three inline forms above are not one class hierarchy (the named and
// assign forms derive from their own count pair), while every list type puts the count pair at
// offset 0 — so `&list` converts to `PtrCnt*` with no adjustment and the emitted argument is
// identical in every matched source.
struct Factory {
    char storage[0x248];
    Factory(CreateFn, u32, const SafeString&, PtrCnt*, const SafeString&, const char*, int);
    ~Factory();
};

#endif
