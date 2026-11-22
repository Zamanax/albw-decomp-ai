#include "albw_types.h"
#include "sead_math.h"
#include "vec3.h"

extern "C" void func_00491338(Mtx33* out, u32 a, u32 b, u32 c);
extern "C" void func_004D7E0C(Mtx33* out, u32 a, u32 b);
extern "C" void func_00115CE4(Vec3* out, const Mtx33* m, const Vec3* v);
extern "C" void func_004356B4(void* p);

struct P {
    u8 pad0[4];
    Vec3 m4;
    u8 pad1[0x58 - 0x10];
    Vec3 m58;
    Mtx33 m64;
};
struct Obj {
    u8 pad0[0x20];
    u32 m20;
    u8 pad1[0x3d0 - 0x24];
    Vec3 m3d0;
    u8 pad2[0x3e8 - 0x3dc];
    u32 m3e8;
    u8 pad3[0x47c - 0x3ec];
    P* m47c;
};
extern "C" void func_002C83FC(Obj* o) {
    P** pp = &o->m47c;
    P* p = *pp;
    func_00491338(&p->m64, o->m20, o->m3e8, 0);
    (*pp)->m58.set(1.6f, 1.0f, 1.0f);
    Vec3 a(0.0f, 0.8f, -0.1f);
    Mtx33 m;
    func_004D7E0C(&m, o->m20, o->m3e8);
    Vec3* pa = &a;
    Mtx33* pm = &m;
    func_00115CE4(pa, pm, pa);
    Vec3& ra = a;
    ra += o->m3d0;
    (*pp)->m4.set(a);
    func_004356B4(*pp);
}
