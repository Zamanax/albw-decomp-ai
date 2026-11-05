#define EN7_EXTRA void f();
#include "../../work5/agent11/en207.h"
f32 func_0051CD84(Random* r, f32 x);
void En7::f() {
    s32 n = (s32)func_0051CD84(func_0058A7D4(this), 30.0f);
    Timer* t = (Timer*)((char*)this + 0x8e4);
    u32 v = n + 60;
    t->start(v);
    m3dc.x = 0.0f;
    m3dc.z = 0.0f;
    func_004FABDC(this, 0, 6, 0);
}
