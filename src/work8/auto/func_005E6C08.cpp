// static initializer, 0x005E6C08: u32 f2l static, Id64/Pair statics, two PtrList<5> + Factory pairs
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
inline s64 f2l(f32 f) { return (s64)f; }

#include "static_init.h"



typedef void* (*CreateFn)();

static s64 data_0070C148 = Id64().v;
static Pair data_0070C150;
static u32 data_0070C140 = (u32)f2l(536870912.0f);
extern void* func_0060862C();
extern const u32 ro_0069308C;
PtrListNamed<5> bss_0075B290;
Factory bss_0075B2B0(func_0060862C, ro_0069308C, "MojPushPullStatue", (PtrCnt*)&bss_0075B290, "\211\237\202\265\210\370\202\253\220\316\221\234", 0, 0);
extern const u32 ro_00693090;
PtrListNamed<5> bss_0075B4F8;
Factory bss_0075B518(func_0060862C, ro_00693090, "MojPushPullLowralStatue", (PtrCnt*)&bss_0075B4F8, "\211\237\202\265\210\370\202\253\220\316\221\234\201\151\203\215\203\105\203\211\203\213\217\351\201\152", 0, 0);
