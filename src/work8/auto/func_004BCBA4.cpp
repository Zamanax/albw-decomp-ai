#include "albw_types.h"

struct S {
    f32 m00, m04, m08, m0c, m10, m14;
    u32 m18;
    u16 m1c;
    u16 m1e;
    u8 m20, m21, m22, m23, m24;
};

void func_004BCBA4(S* s, f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5,
                   u32 v18, u8 v20, u8 v21, u8 v22, u8 v23, u8 v24, u16 v1c, u16 v1e)
{
    s->m00 = a0;
    s->m04 = a1;
    s->m08 = a2;
    s->m0c = a3;
    s->m10 = a4;
    s->m14 = a5;
    s->m18 = v18;
    s->m1c = v1c;
    s->m1e = v1e;
    s->m20 = v20;
    s->m21 = v21;
    s->m22 = v22;
    s->m23 = v23;
    s->m24 = v24;
}
