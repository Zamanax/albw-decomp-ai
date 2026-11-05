// Static initialisation of this unit: two 64-bit/float-global pairs plus the
// shared "resource" block (list, factory, name table, vector) of the purged
// "PlaneObject" enemy.  The block is one class whose static members are laid
// out in declaration order; the initialisation order below is the definition
// order, which is why the factory's payload is placed after the float vector.
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
struct PtrCnt { int num, max; PtrCnt(int n) : num(0), max(n) {} };
struct PtrListBase : PtrCnt { void** ptr; PtrListBase(int n, void* b) : PtrCnt(n), ptr(0) { if (b) ptr = (void**)b; } };
template<int N> struct PtrList : PtrListBase { void* buffer[N]; PtrList() : PtrListBase(N, buffer) {} };
typedef void* (*CreateFn)();
struct Factory {
    char storage[0x248];
    Factory(CreateFn, u32, const SafeString&, PtrListBase*, const SafeString&, const char*, int);
    ~Factory();
};
struct Vec3f { f32 x, y, z; Vec3f() : x(0.0f), y(1.5f), z(1.0f) {} };
extern void* func_0060456C();
extern const u32 ro_006930E0;

struct IdPair { s64 a; s64 b; };
IdPair data_00711028 = { 0, Id64().v };
Pair data_00711038;

struct Res {
    static PtrList<5> list;
    static Factory factory;
    static SafeString strs[4];
    static Vec3f vec;
};

SafeString Res::strs[4] = {
    "N_ArrowT_00",
    "N_ArrowB_00",
    "N_ArrowL_00",
    "N_ArrowR_00"
};
Vec3f Res::vec;
PtrList<5> Res::list;
Factory Res::factory(func_0060456C, ro_006930E0, "PlayerObject", &Res::list,
    "\203\166\203\214\203\103\203\204\201\133\203\111\203\165\203\127\203\106\203\116\203\147", 0, 0);
