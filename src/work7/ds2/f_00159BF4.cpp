typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;

#include "vec3.h"


#include "flags.h"


#include "timer.h"

void func_004FABDC(void* self, s32 a, s32 b, s32 c);   // 0x4FABDC
void func_003C23B8(void* self, s32 a);                 // 0x3C23B8
struct C {
    char pad0[0x3dc];
    Vec3 m3dc;
    char pad1[0x59c - (0x3dc + 12)];
    BitFlag32 m59c;
    char pad2[0x8e0 - 0x5a0];
    char m8e0[4];
    char pad3[0x95c - 0x8e4];
    Timer mTimer;
    char pad4[0x978 - 0x968];
    f32 m978;
    void f();
};
void C::f() {
    m59c.reset(4);
    m59c.reset(0x80);
    m978 = 0.0f;
    m3dc = Vec3(0.0f, 0.0f, 0.0f);
    mTimer.start(0x1e);
    m59c.set(1);
    m59c.set(2);
    func_004FABDC(this, 0, -1, 0);
    func_003C23B8(m8e0, 0x32);
}
