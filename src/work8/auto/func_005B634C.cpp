// static initializer (fam_sti twin 5EC214, retargeted)
typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()

#include "static_init.h"



typedef void* (*CreateFn)();

static s64 data_0070C3D0 = Id64().v;
static Pair data_0070C3D8;
extern u32 func_003C5604(int);
static u32 data_0070C3C8 = func_003C5604(0x36);
extern void* func_00603EF8();
extern const u32 ro_006934C8;
PtrList<5> bss_00764054;
Factory bss_00764074(func_00603EF8, ro_006934C8, "MojWarpSages", &bss_00764054, "\214\253\216\322\202\314\212\324\203\217\201\133\203\166\203\111\203\165\203\127\203\106", 0, 0);
