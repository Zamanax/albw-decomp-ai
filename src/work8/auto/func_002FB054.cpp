#include "albw_types.h"
#include "sead_string.h"
#include "vec3.h"
#include "flags.h"

struct En {
    char p0[0x3d4];
    u32 m3d4;
    char p1[0x3dc - 0x3d8];
    Vec3 m3dc;
    char p2[0x504 - 0x3e8];
    u32 m504;
    char p3[0x59c - 0x508];
    Flag32 m59c;
    char p4[0x90c - 0x5a0];
    u32 m90c;
};

struct Random;
Random* func_0058A7D4(En* e);
u32 func_00111A64(Random* r);
void func_00115D70(Vec3* out, const Vec3& a, f32 s);
void func_00150A84(En* e, const sead::SafeString& name, s32 v);
extern u32 data_0070B478;

void func_002FB054(En* e) {
    En * t1 = e;
    t1->m59c.reset(4);
    t1->m59c.reset(0x80);
    e->m59c.set2(0x800);
    e->m90c = e->m3d4;
    Vec3* p = &e->m3dc;
    *p *= 0.2f;
    Random* r = (func_0058A7D4(e));
    u32 m = data_0070B478 << 1;
    e->m504 = (u32)(((u64)func_00111A64(r) * m) >> 32) - data_0070B478;
    func_00150A84(e, sead::SafeString("SE_StalfosBone_HIT"), 0);
}
