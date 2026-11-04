#define EN_EXTRA void f();
#ifndef EN2_002BD210_H
#define EN2_002BD210_H
#include "albw_types.h"


#include "vec3.h"


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

struct En;
void func_004F88A0(En* e, u32 v);
void func_004FC07C(En* e, s32 a, s32 b, s32 c);

struct Sub800 {
    char p0[0x11c];
    u32 m91c;           // En+0x91c
    char p120[0x13c - 0x120];
    Timer t;            // En+0x93c
};

struct En {
    char p0[0x3dc];
    Vec3 m3dc;          // 0x3dc
    char p3e8[0x800 - 0x3e8];
    Sub800 m800;        // 0x800
    char p948[0x95c - 0x948];
    u8 m95c;            // 0x95c
    EN_EXTRA
};
#endif
void En::f() {
    func_004F88A0(this, m800.m91c);
    m95c = 1;
    m3dc.x = 0.0f; m3dc.y = 0.0f; m3dc.z = 0.0f;
    func_004FC07C(this, 4, -1, 0);
    u32 n = 0x1e; Timer& t = m800.t; t.start(n);
}
