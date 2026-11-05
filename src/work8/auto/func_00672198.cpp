#include "albw_types.h"
#include "vec3.h"

extern "C" void func_002F8DE4(void*, s32, s32, s32);
extern "C" s32 func_002F93C8(void*, s32);
extern "C" s32 func_004904CC(f32, f32);
extern "C" void func_0014FAFC(void*, s32, f32);
extern "C" void func_0065AE94(void*, s32);
extern "C" void func_003931EC(void*, s32);
extern "C" void func_0065AF00(void*);

void func_00672198(u8* p) {
    func_002F8DE4(p, 1, -1, 1);
    u32* cnt = (u32*)(p + 0x988);
    *cnt = 0;
    u8 b = *(u8*)(p + 0x90a);
    if (b != 0) {
        *(u32*)(p + 0x97c) = 0;
    } else {
        *(u32*)(p + 0x97c) = 0x12c;
    }
    if (func_002F93C8(p, 1) == 0) {
        func_0065AE94(p + 0x90c, 0);
        u8* q = p + 0x90c;
        func_003931EC(q, 0);
        func_0065AF00(q);
    } else {
        Vec3 d(*(const Vec3*)(p + 0x8d0), *(const Vec3*)(p + 0x3d0));
        s32 ang = func_004904CC(d.x, d.z);
        s32* dst = (s32*)(p + 0x8dc);
        *dst = ang;
        s32 t = *(s32*)(p + 0x3e8);
        f32* q8 = (f32*)(p + 0x800);
        if (t != ang) {
            *(f32*)(p + 0x3dc) = 0.0f;
            *(f32*)(p + 0x3e4) = 0.0f;
        } else {
            func_0014FAFC(p, t, q8[0x39]);
        }
    }
    *(u8*)(p + 0x98d) = 0;
    *(u8*)(p + 0x98f) = 1;
    *(u8*)(p + 0x990) = 0;
}
