#define EN_EXTRA void f();
#include "../../work5/agent9/en202.h"
void func_004FABDC(En202* e, s32 a, s32 b, s32 c);
void En202::f() {
    func_004FABDC(this, 0, -1, 0);
    Timer* t = (Timer*)((char*)this + 0x8e0);
    t->start(randU32(func_0058A7D4(this), 120) + 120);
    *((u8*)this + 0x94f) = 0;
}
