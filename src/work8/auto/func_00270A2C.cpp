#include "albw_types.h"
#include "sead_math.h"
struct State41D {s32 a; u32 b; f32 c; Vec2 limits; f32 d; u32 e; u8 f; u8 pad[7]; s8 g; u8 h; u8 i;};
void func_00270A2C(State41D* p) {
    p->a = -1;
    State41D * t1 = p;
    t1->b = 0;
    t1->c = 0.f;
    State41D * t3 = p;
    p->limits.x = 0.f;
    t3->limits.y = 1.f;
    State41D * t2 = t3;
    t2->d = 0.f;
    t2->e = 0;
    t2->f = 0;
    State41D * t0 = t2;
    t0->g = -1;
    t0->h = 0;
    t2->i = 1;
}
