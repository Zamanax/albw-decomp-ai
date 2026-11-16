#include "vec3.h"

typedef unsigned int u32;
typedef float f32;

struct Obj28 {
    char p0[0x40c];
    u32 m40c;
    char p1[0x498 - 0x410];
    u32 m498;
    Vec3 v49c;
    char p2[0x4ac - 0x4a8];
    f32 m4ac;
    char p3[0x4bc - 0x4b0];
    f32 m4bc;
    f32 m4c0;
};

extern "C" void func_003249E0(Obj28* p, u32 a1);
extern "C" void func_00324964(Obj28* p);
extern "C" f32 func_0054DE3C(Obj28* p, u32 a1, u32 a2);

void func_00325AB0(Obj28* p, u32 a1) {
    func_003249E0(p, a1);
    func_00324964(p);
    u32 t = p->m40c;
    p->m498 = t;
    f32 r1 = func_0054DE3C(p, a1, 1);
    p->m4c0 = r1;
    p->m4bc = r1;
    f32 t0 = func_0054DE3C(p, a1, 0);
    f32 r2 = t0;
    p->m4ac = r2;
    (&p->v49c)->set(0.0f, r2, 0.0f);
}
