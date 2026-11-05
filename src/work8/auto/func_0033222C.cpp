typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;

#include "timer.h"

struct Sub {
    char p0[0x94];
    u8 m94;
    char p1[0xbc - 0x95];
    u8 mbc;
    char p2[0xc5 - 0xbd];
    u8 mc5;
    char p3[0xe4 - 0xc6];
    Timer timer;
};
struct C {
    char pad0[0x400];
    Sub sub;
    char pad1[0x514 - (0x400 + sizeof(Sub))];
    u8 m514;
};
void func_002E01FC(C* self);                   // 0x2E01FC
void func_001E4090(C* self, s32 a);            // 0x1E4090
void func_001E405C(C* self, s32 a);            // 0x1E405C
void func_001E43F8(C* self, f32 v);            // 0x1E43F8
void func_001E43DC(C* self, f32 v);            // 0x1E43DC
f32 func_0052F864(C* self);                    // 0x52F864
extern "C" void func_0033222C(C* self) {
    self->sub.m94 = 1;
    Sub* s = &self->sub;
    if (s->mbc == 0) {
        if (s->mc5 != 5) self->m514 = 1;
    }
    func_002E01FC(self);
    func_001E4090(self, 0);
    func_001E405C(self, 0);
    func_001E43F8(self, 1.0f);
    func_001E43DC(self, 1.0f);
    Timer* t = &self->sub.timer;
    u32 n = (u32)func_0052F864(self);
    t->start(n);
}
