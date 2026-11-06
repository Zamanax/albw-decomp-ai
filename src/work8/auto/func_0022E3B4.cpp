#include "../../work7/ds2/ds2.h"
#include "vec3.h"
struct A68 { Vec3 v; f32 mC; f32 m10; };
f32 func_0051CF68(void*, f32, f32, f32);
u32 func_0052F654(void*);
u32 func_0058A8F0(void*);
void func_0065E9FC(void*, u32);
Vec3* func_00520FC0(void*);
void func_00115C70(Vec3*, const Vec3*, const Vec3*);
s32 func_0068C690(const Vec3*);

struct ThisE7 {
    char pad0[0x3d0];
    Vec3 m3d0;
    char pad1[0x3e8 - 0x3dc];
    u32 m3e8;
    char pad2[0xa68 - 0x3ec];
    A68* mA68;
    char pad3[0xa6d - 0xa6c];
    u8 m_a6d;
    char pad4[0xa70 - 0xa6e];
    Vec3 m_a70;
    u32 m_a7c;
};

static inline const Vec3* chooseTarget(ThisE7* t) {
    if (t->m_a6d) return (const Vec3*)func_00520FC0(t);
    return &t->m_a70;
}
void func_0022E3B4(ThisE7* t) {
    A68* p = t->mA68;
    p->m10 = func_0051CF68(&p->mC, p->v.x, p->v.y, p->v.z);
    t->m3e8 = func_0052F654(t->mA68);
    if (t->mA68->mC == 1.0f && func_0058A8F0(t)) {
        const Vec3* a = chooseTarget(t);
        Vec3 d;
        Vec3 tmp;
        func_00115C70(&tmp, a, &t->m3d0);
        d = tmp;
        func_0068C690(&d);
        func_0065E9FC(&t->m_a7c, 4);
    }
}
