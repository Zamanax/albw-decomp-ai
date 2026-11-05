typedef unsigned int u32; typedef long long s64;
#pragma pack(4)

#include "static_init.h"

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
extern char g_006F5948;
static s64 g_00716730 = Id64().v;
static Pair g_00716738;
struct T_00716728 { u32 m0; T_00716728() : m0((u32)&g_006F5948) {} };
static T_00716728 g_00716728;
