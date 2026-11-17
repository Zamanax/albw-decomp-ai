#include "albw_types.h"
#include "vec3.h"

extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_0068C690(const Vec3& v);

struct Obj {
    char p0[0x24];
    u32 m24;
    char p1[0x3d0 - 0x28];
    Vec3 m3d0;
    char p2[0x9d9 - 0x3dc];
    u8 m9d9;
};

extern "C" u32 func_0024540C(Obj* self) {
    if (self->m9d9 == 2) {
        Vec3 p = *func_00520FC0(self);
        Vec3 d = p - self->m3d0;
        return func_0068C690(d);
    }
    return self->m24;
}
