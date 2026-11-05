// static initializer (fam_sti twin 5EC214, retargeted)
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
inline s64 f2l(f32 f) { return (s64)f; }
struct PtrCnt { int num, max; PtrCnt(int n) : num(0), max(n) {} };
struct PtrListBase : PtrCnt { void** ptr; PtrListBase(int n, void* b) : PtrCnt(n), ptr(0) { if (b) ptr = (void**)b; } };
template<int N> struct PtrList : PtrListBase { void* buffer[N]; PtrList() : PtrListBase(N, buffer) {} };
typedef void* (*CreateFn)();
struct Factory {
    char storage[0x248];
    Factory(CreateFn, u32, const SafeString&, PtrListBase*, const SafeString&, const char*, int);
    ~Factory();
};
static s64 data_0070F750 = Id64().v;
static Pair data_0070F758;
static u32 data_0070F740 = (u32)f2l(0.0f);
static u32 data_0070F744 = data_0070F740;
static u32 data_0070F748 = data_0070F740;
extern void* func_00605504();
extern const u32 ro_006932B0;
PtrList<5> bss_0078B338;
Factory bss_0078B358(func_00605504, ro_006932B0, "ObjMapleBroom", &bss_0078B338, "\203\101\203\103\203\212\203\223\202\314\342\264", 0, 0);
