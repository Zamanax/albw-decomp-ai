typedef unsigned int u32; typedef long long s64;
#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()
extern char g_00725970;
static s64 g_0070D828 = Id64().v;
static Pair g_0070D830;
struct T_0070D820 { u32 m0; T_0070D820() : m0((u32)&g_00725970) {} };
static T_0070D820 g_0070D820;
