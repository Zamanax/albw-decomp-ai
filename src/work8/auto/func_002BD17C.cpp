typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;

#include "timer.h"

struct C {
    char pad0[0x3dc];
    f32 m3dc, m3e0, m3e4;
    char pad1[0x91c - 0x3e8];
    s32 m91c;
    char pad2[0x93c - 0x920];
    Timer mTimer;
    char pad3[0x95c - 0x948];
    u8 m95c;
    void f();
};
void func_004F88A0(C* self, s32 a);
void func_004FABDC(C* self, s32 a, s32 b, s32 c);
f32 func_0058AC38(C* self);
void C::f() {
    func_004F88A0(this, m91c);
    m95c = 1;
    func_004FABDC(this, 5, -1, 0);
    m3e0 = m3dc = 0.0f; m3e4 = 0.0f;
    Timer* t = &mTimer;
    t->start(((s32)((((((func_0058AC38(this)))))))));
}
