#include "albw_types.h"
#include "vec3.h"

extern "C" void func_00115C54(Vec3*, const Vec3&, const Vec3&);

struct Blk36 { Vec3 v[3]; };
struct Set36 { s32 n; u32 f4; Blk36* d; };

extern "C" void func_00432DF0(Set36* s, const Vec3* b) {
    for (s32 i = 0; i < s->n; i++) {
        for (s32 j = 0; j < 3; j++) {
            Set36 * t0 = s;
            Vec3* p = &((u32)i < (u32)t0->n ? t0->d[i] : t0->d[0]).v[j];
            func_00115C54(p, *p, *b);
        }
    }
}
