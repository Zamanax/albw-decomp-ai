typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Random;
struct En;
u32 func_00111A64(Random* r);
Random* func_0058A7D4(En* e);
f32 func_0051CD84(Random* r, f32 x);
void func_004FABDC(En* e, s32 a, s32 b, s32 c);

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
    void start(u32 n, u32 c = 0) {
        max = n;
        if (n) rate = 1.0f / n;
        else rate = 0.0f;
        cur = c;
    }
};

struct BitFlag32 {
    u32 v;
    void set(u32 b) { v |= b; }
};


#include "vec3.h"


struct En {
    char p0[0x3dc];
    Vec3 m3dc;
    char p3e8[0x59c - 0x3e8];
    BitFlag32 m59c;
    char p5a0[0x8e0 - 0x5a0];
    Timer m8e0;
    void f();
};

void En::f() {
    m59c.set(0x80);
    s32 n = (s32)func_0051CD84(func_0058A7D4(this), 30.0f);
    Timer* t = &m8e0;
    u32 m = (u32)n + 30;
    t->start(m);
    m3dc.x = 0.0f;
    m3dc.z = 0.0f;
    func_004FABDC(this, 3, -1, 0);
}
