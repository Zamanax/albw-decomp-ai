// static initializer (fam_sti twin 5EC214, retargeted)
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
inline s64 f2l(f32 f) { return (s64)f; }

#include "static_init.h"



typedef void* (*CreateFn)();

static s64 data_0070F750 = Id64().v;
static Pair data_0070F758;
static u32 data_0070F740 = (u32)f2l(0.0f);
static u32 data_0070F744 = data_0070F740;
static u32 data_0070F748 = data_0070F740;
extern void* func_00605504();
extern const u32 ro_006932B0;
PtrList<5> bss_0078B338;
Factory bss_0078B358(func_00605504, ro_006932B0, "ObjMapleBroom", &bss_0078B338, "\203\101\203\103\203\212\203\223\202\314\342\264", 0, 0);
