typedef unsigned int u32; typedef long long s64; typedef float f32; typedef unsigned char u8; typedef unsigned short u16;

#include "sead_string.h"

#pragma pack(4)

struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()

#include "static_init.h"

struct Disposer49BA {
    Disposer49BA();
    virtual ~Disposer49BA();
};

struct T_00716750 { s64 v; };
static T_00716750 data_00716750 = { Id64().v };
static Pair data_00716758;
static sead::FixedSafeString<0x400> g_007A82A0;
static Disposer49BA g_007A86AC;
