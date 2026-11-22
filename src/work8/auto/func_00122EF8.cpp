#include "albw_types.h"
extern "C" float sqrtf(float);
extern "C" s32 func_004904CC(f32, f32);
struct Ang { char p[0x8f0]; u32 c0; u32 c1; u32 c2; };
void func_00122EF8(Ang* s, const f32* v, f32* a, u32* b, u32* c) {
    if (s->c0) s->c0--;
    Ang * t0 = s;
    if (t0->c1) t0->c1--;
    f32 z = 0.0f;
    if (t0->c0 != 0) {
        *a = z;
    } else {
        f32 len = sqrtf(v[0] * v[0] + v[1] * v[1]);
        *a = len;
        if (*(s32*)&len > 0x3f800000) len = 1.0f;
        *a = len;
        if (t0->c1 != 0) {
            if (s->c1 <= s->c2) {
                *a = (((f32)(s->c2 - s->c1)) / ((f32)s->c2)) * *a;
            }
        }
    }
    u32 r = func_004904CC(v[1], v[0]) + 0x40000000;
    *c = r;
    *b = r;
}
