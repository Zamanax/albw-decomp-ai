typedef unsigned char u8; typedef unsigned int u32; typedef int s32; typedef float f32;

#include "vec3.h"

extern "C" const Vec3 bss_007A9260;
extern "C" s32 data_0070A938;
extern "C" s32 data_0070A93C;
struct En;
void func_002A27C4(En* e, s32 v);
Vec3* func_00520FC0(En* e);
void func_00115C70(Vec3* out, const Vec3* a, const Vec3* b);
s32 func_0068C690(const Vec3* v);
void func_0051D2F4(s32* cur, s32 tgt, f32 rate, s32 a, s32 b);
void func_0051D39C(s32* ang, s32 target, s32 step);
bool func_0058A8F0(En* e);
f32 func_0058AC38(En* e);
void func_00662128(void* p, s32 v);

struct En {
    u8 pad[0x3d0]; Vec3 m3d0; u8 pad3dc[0x3e8 - 0x3dc]; s32 m3e8;
    u8 pad3ec[0x9e0 - 0x3ec]; u8 m9e0[0xb80 - 0x9e0]; s32 mb80;
};

extern "C" void func_002A6B9C(En* e) {
 Vec3 d = *(&bss_007A9260);
    { Vec3* pd = &d;func_00115C70(pd, func_00520FC0(e), &e->m3d0); }
    func_002A27C4(e, 0);
    f32 f = (func_0058AC38(e)) - 1.0f;
    func_0051D39C(&e->mb80, data_0070A938, (int)f);
    s32 t0 = func_0068C690(&d);
    u32 t6 = e->mb80;
    s32 t3 = t6;
    func_0051D2F4(&e->m3e8, t0, 1.0f, data_0070A93C, t3);
    bool t4 = (func_0058A8F0(e));
    if (t4) func_00662128(e->m9e0, 1);
}
