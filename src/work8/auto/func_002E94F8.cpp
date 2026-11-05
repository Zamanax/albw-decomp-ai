#define EN_EXTRA void f();
#include "../../work5/agent16/en213.h"
extern "C" u32 func_00548E78(void* p, s32 a, s32 b);
void En::f() {
    En* self = this;
    self->m59c.set(4); self->m59c.set(0x80); self->m59c.set(1); self->m59c.set(2);
    func_004FC07C(self, 1, -1, 0);
    if (*((u8*)self + 0x8cd) != 0x21) {
        u32* p = (u32*)((char*)self + 0xb0c);
        u32 t = func_00548E78(self, 0x3c, 0x19);
        u32 z = 0;
        p[1] = t;
        if (t == 0) {
            ((f32*)p)[2] = 0.0f;
        } else {
            ((f32*)p)[2] = 1.0f / (f32)t;
        }
        p[0] = z;
    }
}
