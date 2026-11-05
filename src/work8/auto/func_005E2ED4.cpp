// static initializer (target 0x005E2ED4)
typedef unsigned int u32; typedef long long s64; typedef float f32;

#include "sead_string.h"

#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
struct Vec3 { f32 x, y, z; Vec3() : x(0), y(0), z(0) {} };
struct PtrCnt { int num, max; PtrCnt(int n) : num(0), max(n) {} };
struct PtrListBase : PtrCnt { void** ptr; PtrListBase(int n, void* b) : PtrCnt(n), ptr(0) { if (b) { void** t = static_cast<void**>(b); ptr = t; } } };
template<int N> struct PtrList : PtrListBase { void* buffer[N]; PtrList() : PtrListBase(N, buffer) {} };
typedef void* (*CreateFn)();
struct Factory {
    char storage[0x248];
    Factory(CreateFn, u32, const SafeString&, PtrListBase*, const SafeString&, const char*, int);
    ~Factory();
};
extern void* func_00607F30();
extern const u32 ro_006931A8;

struct Res {
    static PtrList<5> list;
    static Factory factory;
    static SafeString strs[4];
    static SafeString strs3[3];
    static Vec3 vec;
};

s64 data_0070FAD0 = Id64().v;
Pair data_0070FAD8;
SafeString Res::strs[4] = {
    "N_ArrowT_00",
    "N_ArrowB_00",
    "N_ArrowL_00",
    "N_ArrowR_00"
};
SafeString Res::strs3[3] = {
    "up",
    "wait",
    "get"
};
SafeString data_0070FAE0 = "TriForce_get_event";
Vec3 Res::vec;
PtrList<5> Res::list;
Factory Res::factory(func_00607F30, ro_006931A8, "ObjTriForceBrave", &Res::list, "\227E\213C\202\314\202\251\202\275\202\334\202\350", 0, 0);
