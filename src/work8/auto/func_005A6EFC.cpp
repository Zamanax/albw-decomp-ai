typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;
struct SafeString { const char* text; SafeString(const char* s) : text(s) {} virtual ~SafeString() {} };
#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()

#include "vec3.h"

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
static s64 data_0070F610 = Id64().v;
static Pair data_0070F618;
static Vec3 data_007891F4(0.0f, 0.0f, 0.8f);
static Vec3 data_00789200(0.0f, 0.0f, 0.4f);
static u32 data_0070F608 = (u32)f2l(178956976.0f);
extern "C" void* func_00602F24();
extern "C" const u32 ro_00693164;
PtrList<5> data_00788F8C;
Factory data_00788FAC(func_00602F24, ro_00693164, "ObjJavelin", &data_00788F8C, "\223\212\221\204", 0, 0);
