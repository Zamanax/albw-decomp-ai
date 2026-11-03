#include "../../work5/agent10/en204.h"
struct En2Inner {
    char p0[0xf4];
    Timer mt;
};
struct En2A {
    char p0[0x800];
    En2Inner in;
};
s32 func_0058AB74(En* e);
f32 func_0058AA40(En* e);
void func_004FB0A4(En* e, f32 r);
void func_004FEDAC(En* e) {
    if (func_0058AB74(e) == 1) {
        f32 t = func_0058AA40(e);
        func_004FC07C(e, 0, -1, 0);
        func_004FB0A4(e, t);
    } else {
        func_004FC07C(e, 0, -1, 0);
    }
    En2A* a = (En2A*)e;
    e->m3dc.x = 0.0f;
    e->m3dc.z = 0.0f;
    a->in.mt.start(randU32(func_0058A7D4(e), 150) + 30);
}
