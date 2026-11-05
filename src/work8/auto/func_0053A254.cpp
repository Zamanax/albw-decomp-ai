typedef unsigned int u32;
typedef int s32;
typedef float f32;


#include "vec3.h"


#include "sead_math.h"

struct Obj { char p0[0x3d0]; Vec3 m3d0; char p3dc[0x3e8-0x3dc]; s32 m3e8; };

static inline unsigned l2c_fbits(float x) { union { float f; unsigned u; } v; v.f = x; return v.u; }

extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_0068C690(const Vec3& v);
extern "C" u32 func_0058E2B8(const AngleT& a);

inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r; func_00115C70(&r, &a, &b); return r; }

extern "C" bool func_0053A254(Obj* a0) {
    Vec3 d = *func_00520FC0(a0) - a0->m3d0;
    s32 a = func_0068C690(d);
    if ((int)(l2c_fbits(d.x * d.x + d.z * d.z)) < 0x42440000) {
        if (func_0058E2B8(AngleT(a - a0->m3e8)) < 0x40000000) return 1;
    }
    return 0;
}
