#include "albw_types.h"
#include "vec3.h"
#include "sead_math.h"
extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_0068C690(const Vec3& v);
extern "C" u32 func_0058E2B8(const AngleT& a);

struct Lim { s32 v; Lim(s32 n) : v(n) {} };

void func_001A91A8(void* self) {
    u8* p = (u8*)self;
    Vec3 e;
    Vec3 d;
    func_00115C70(&d, func_00520FC0(self), (const Vec3*)(p + 0x3d0));
    e = d;
    s32 v = func_0068C690(e) - *(s32*)(p + 0x3e8);
    Lim c(0x3c71c6e0);
    s32 out;
    if (func_0058E2B8(*(const AngleT*)&v) >= (s32)c.v) {
        out = 0;
    } else {
        s32 nc = -c.v;
        if (v < nc) v = nc;
        else if (c.v < v) v = c.v;
        out = v;
    }
    *(s32*)(p + 0x944) = out;
}
