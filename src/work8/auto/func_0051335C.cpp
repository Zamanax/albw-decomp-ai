#include "vec3.h"
#include "albw_types.h"
extern "C" void func_00115C54(Vec3*, const Vec3&, const Vec3&);
extern "C" s32 func_00512E74(void*);
extern "C" void func_0066B94C(void*, u32);

extern "C" void func_0051335C(char* self) {
    Vec3* d = (Vec3*)(self + 0x3d0);
    d->setAdd(*d, *(Vec3*)(self + 0x3dc));
    *(float*)(self + 0x3e0) = *(float*)(self + 0x3e0) - 0.02f;
    if (*(s32*)(self + 0x48c) > 30) {
        if (func_00512E74(self) != 0) *(float*)(self + 0x3e0) = -0.02f;
    }
    float diff = *(float*)(self + 0xc) - *(float*)(self + 0x3d4);
    if (diff > 0.0f) { } else { diff = -diff; }
    union { float f; s32 i; } u;
    u.f = diff;
    float* z = (float*)(self + 0x3e0);
    if (*z < 0.0f && u.i < 0x3f800000) func_0066B94C(self + 0x48c, 0xd);
}
