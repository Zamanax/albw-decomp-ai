typedef unsigned int u32; typedef long long s64;
#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
static s64 g_00709A40 = Id64().v;
static Pair g_00709A48;
struct T_00709A38 { u32 m0; T_00709A38() : m0(0x27100000) {} };
static T_00709A38 g_00709A38;
