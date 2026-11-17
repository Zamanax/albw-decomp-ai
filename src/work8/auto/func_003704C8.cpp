#include "vec3.h"
#include "albw_types.h"

extern const Vec3 data_007A9260;
extern u32 data_00708920[];

struct Obj003704C8 {
    Vec3 v0;
    u32 wc;
    u8 a10, a11;
    u8 a12, a13;
    u8 a14, a15;
    u8 a16, a17;
    u16 h18, h1a;
    Vec3 v1c, v28, v34, v40;
};

extern "C" void func_003704C8(Obj003704C8* p) {
    u8 z = 0;
    p->a12 = z;
    p->a13 = z;
    p->a16 = 1;
    p->a17 = z;
    p->h18 = (u16)-1;
    p->h1a = z;
    const Vec3* zv = &data_007A9260;
    p->v1c.setCopy(*zv);
    p->v28.setCopy(*zv);
    p->v34.setCopy(*zv);
    p->v40.setCopy(*zv);
    p->v0.set(0.f, 0.f, 0.f);
    p->wc = data_00708920[1];
    p->a10 = z;
    p->a11 = z;
    p->a14 = z;
    p->a15 = z;
}
