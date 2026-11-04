typedef unsigned char u8; typedef unsigned int u32; typedef int s32; typedef float f32;

#include "vec3.h"

struct AngleT { s32 v; AngleT(s32 n) : v(n) {} };
extern "C" void* data_0070FB60;
extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_004905E0(f32);
extern "C" u32 func_0058E2B8(const AngleT& a);
inline s32 atan2Idx(f32 y, f32 x) {
    if (x == 0.0f && y == 0.0f) return 0;
    if (x >= 0.0f) {
        if (y >= 0.0f) {
            if (x >= y) return func_004905E0(y / x);
            else return 0x40000000 - func_004905E0(x / y);
        } else {
            if (x >= -y) return -func_004905E0(-y / x);
            else return 0xc0000000 + func_004905E0(x / -y);
        }
    } else {
        if (y >= 0.0f) {
            if (-x >= y) return 0x80000000 - func_004905E0(y / -x);
            else return 0x40000000 + func_004905E0(-x / y);
        } else {
            if (x <= y) return 0x80000000 + func_004905E0(y / x);
            else return 0xc0000000 - func_004905E0(x / y);
        }
    }
}
extern "C" s32 data_0070A7E4;
extern "C" void func_0051D27C(s32* a, s32 target, s32 b);
struct Obj { char p0[0x3d0]; Vec3 m3d0; char p3dc[0x3e8-0x3dc]; s32 m3e8; char p3ec[0x8c0-0x3ec]; u8 m8c0; };
extern "C" void func_00211574(Obj* o) {
    switch (o->m8c0) {
    case 1: case 2: case 3: case 4: case 5: case 6: {
        Vec3 v;
        Vec3* pv = &v;
        func_00115C70(pv, func_00520FC0(o), &o->m3d0);
        s32 ang = atan2Idx(v.x, v.z);
        func_0051D27C(&o->m3e8, ang, data_0070A7E4);
        break;
    }
    default:
        break;
    }
}
