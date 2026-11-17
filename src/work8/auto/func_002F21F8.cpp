#include "flags.h"
typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Sub { u32 a; u32 b; f32 c; };
struct Obj {
    char pad0[0x59c];
    BitFlag32 m59C;
    char pad5a0[0xb0c - 0x5a0];
    Sub sub;
    char pad_b18[0xb98 - 0xb18];
    f32 mB98;
};
extern "C" s32 func_0058AB74(void*);
extern "C" void func_004FABDC(void*, u32, s32, s32);
extern "C" void func_002F21F8(Obj* self) {
    self->m59C.set(4);
    self->m59C.set(0x80);
    self->m59C.set(1);
    self->m59C.set(2);
    Sub* s = &self->sub;
    s->b = 30;
    s->c = 0.033333335f;
    s->a = 0;
    s32 r = func_0058AB74(self);
    if (r == 0x1b || r == 0x1c || r == 0x1d) {
    } else {
        func_004FABDC(self, 0x18, -1, 0);
    }
    self->mB98 = 0.0f;
}
