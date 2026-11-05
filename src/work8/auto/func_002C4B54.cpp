typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct En;
void func_004FC07C(En* e, s32 a, s32 b, s32 c);

#include "timer.h"

struct Ctr {
    u32 v;
    u32 add(u32 d) { v += d; return v; }
};
struct En {
    char p0[0x3e8];
    s32 m3e8;
    char p3ec[0x8e0 - 0x3ec];
    Ctr m8e0;
    u32 m8e4;
    Timer m8e8;
    f32 m8f4;
    void f();
};
void En::f() {
    u32 t = m8e0.add(0x80000000u);
    t += 0x20000000u;
    m8e4 = t & 0xc0000000u;
    m3e8 = 0;
    func_004FC07C(this, 0, 0, 0);
    m8f4 = 0.0f;
    m8e8.start(60);
}
