#include "albw_types.h"
#include "vec3.h"

struct Sub {
    u8 pad0[0x75];
    u8 m475;
    u8 pad1[0x78 - 0x76];
    Vec3 m478;
    Vec3 m484;
};

struct Obj {
    u8 pad0[0x3dc];
    f32 m3dc;
    f32 m3e0;
    f32 m3e4;
    u8 pad1[0x400 - 0x3e8];
    Sub sub;
    Vec3 m490;
    Vec3 m49c;
};
extern "C" void func_001E5B90(Obj* o, u8 v, f32 a, f32 b, f32 c, f32 d, f32 e) {
    o->sub.m475 = v;
    Vec3 t; t.set(a, b, c);
    Vec3* p3 = &o->m490;
    Vec3* p1 = &o->sub.m478;
    Vec3* p2 = &o->sub.m484;
    Vec3 * t0 = p1;
    t0->setCopy(t);
    p2->setCopy(t);
    Vec3 * t1 = p3;
    t1->setCopy(t);
    o->m49c.setCopy(t);
    o->m49c.z = c + d;
    o->m3dc = 0.0f;
    o->m3e0 = 0.0f;
    o->m3e4 = e;
}
