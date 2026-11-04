typedef unsigned char u8;
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


struct Sub420 {
    char pad[0x22];
    u8 m22;
};

struct En {
    char p0[0x3dc];
    Vec3 m3dc;
    char p3e8[0x420 - 0x3e8];
    Sub420* m420;
    char p424[0x59c - 0x424];
    BitFlag32 m59c;
    char p5a0[0x8e4 - 0x5a0];
    Timer m8e4;
    char p8f0[0xa30 - 0x8f0];
    u8 ma30;
    void f();
};

void En::f() {
    Sub420* p = m420;
    p->m22 = 0;
    m59c.set(0x80);
    if (ma30) {
        s32 n = (s32)func_0051CD84(func_0058A7D4(this), 30.0f);
        m8e4.start((u32)n + 100);
        ma30 = 0;
    } else {
        m8e4.start(100);
    }
    m3dc.x = 0.0f;
    m3dc.z = 0.0f;
    func_004FABDC(this, 0, -1, 0);
}
