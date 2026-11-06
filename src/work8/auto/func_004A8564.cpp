#include "albw_types.h"
#include "vec3.h"

extern "C" void func_00432F74(void* self);
extern "C" void func_004A8334(void* self, void* q, u32 one, void* o, u32 a, u32 b);

struct Obj {
    u32 vt;
    Vec3 m4;
    Vec3 m10;
    Vec3 m1c;
    u8 pad28[0x30];
    u32 m58;
    Obj() { func_00432F74(this); }
    void setPair(const Vec3& v) { m1c = v; m10 = v; }
};

struct Q { f32 f[15]; };

static inline Vec3 add3(const Vec3& a, const Vec3& b) { Vec3 r; r.setAdd(a, b); return r; }

extern "C" void func_004A8564(void* self, Q* p, u32 a, u32 b) {
    Obj o;
    o.m4 = add3(*(const Vec3*)&p->f[12], **(const Vec3**)&p->f[7]);
    o.setPair(add3(*(const Vec3*)&p->f[12], **(const Vec3**)&p->f[8]));
    o.m58 = *(u32*)&p->f[11];
    Q q = *p;
    func_004A8334(self, &q, 1, &o, a, b);
}
