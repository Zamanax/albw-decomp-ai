#include "albw_types.h"
#include "vec3.h"

struct Arg4F { u32 m0; Vec3 m4; };
struct En { u8 pad0[0x8d4]; s32 m8d4; u32 m8d8; u8 pad1[4]; u8 m8e0; };

s32 func_0068C690(const Vec3& v);
s32 func_004F4A68(En* e, Arg4F* p);

s32 func_00201D4C(En* e, Arg4F* p) {
    s32 r = func_004F4A68(e, p);
    if (0 != r && e->m8e0 == 0) {
        f32 y = p->m4.y;
        if ((y > 0.0f ? y : -y) < 0.4f) {
            int ang = func_0068C690(p->m4);
            u32 m = e->m8d8; u32 h = m; h += 0x80000000u; u32 d = (u32)ang - h;
            if (d - 0xc0000001u < 0x7fffffffu) {
                u32 t = d + 0x80000000u;
                e->m8d4 = (s32)(t + (m + d));
            }
        }
    }
    return r;
}
