#include "albw_types.h"
#include "vec3.h"

extern "C" void func_00115C54(Vec3*, const Vec3*, const Vec3*);
extern "C" void func_0065FCF8(void*, s32);

struct S {
    u8 pad0[0x3d0];
    Vec3 a;
    Vec3 b;
    u8 pad1[0x4fc - 0x3e8];
    s32 state;
    u8 pad2[0x550 - 0x500];
    f32 f;
};

extern "C" void func_00252160(S* p) {
    f32& f = p->f;
    f32 delta = 0.8f - f;
    f = f + delta * 0.1f;
    Vec3* a = &p->a;
    func_00115C54(a, a, &p->b);
    s32 n = p->state;
    if (n > 20) {
        func_0065FCF8(&p->state, 6);
    }
}
