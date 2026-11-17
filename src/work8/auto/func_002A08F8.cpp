typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

#include "flags.h"
#include "timer.h"

void func_002AFEC4(void* self, s32 a, s32 b);
void func_004FC07C(void* self, s32 a, s32 b, s32 c);

struct C {
    char pad0[0x59c];
    BitFlag32 m59c;
    char pad1[0x895 - 0x5a0];
    u8 m895;
    char pad2[0x900 - 0x896];
    f32 m900;
    char pad3[0x910 - 0x904];
    Timer mTimer;

    void f() {
        m59c.set(1);
        m59c.set(0x80);
        m59c.set(4);
        m900 = 0.0f;
        mTimer.start(0x78);
        m895 = 0;
        func_002AFEC4(this, -1, -1);
        func_004FC07C(this, 4, -1, 0);
    }
};

void func_002A08F8(C* self) { self->f(); }
