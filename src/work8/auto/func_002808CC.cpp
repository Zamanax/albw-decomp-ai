#include "albw_types.h"
#include "vec3.h"

extern void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);

struct Ctx {
    u8 _p0[0x368];
    Vec3 m368;
    u8 _p1[0x5c];
    Vec3 m3d0;
    f32 m3dc;
    u8 _p2[4];
    f32 m3e4;
};

void func_002808CC(Ctx* self) {
    Vec3 t;
    Vec3* o = &t;
    const Vec3* a = &self->m3d0;
    const Vec3* b = &self->m368;
    func_00115C70(o, *a, *b);
    f32 x = t.x;
    self->m3dc = x;
    self->m3e4 = t.z;
}
