#include "../../../src/work6/gpt13/en218.h"
#include "../../../src/work6/gpt13/atan.h"
void func_004D80A4(Vec3* out, s32 ang, f32 len);
void func_00536CA4(void* self, Vec3* out, Vec3 a, const Vec3& b, f32 len) {
    Vec3 d;
    d.setSub(a, b);
    f32 y = d.x;
    f32 x = d.z;
    s32 ang = atan2Idx(y, x);
    func_004D80A4(out, ang, len);
    out->y = 0.0f;
}
