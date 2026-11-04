#define EN_EXTRA void f();
#include "../../work5/agent9/en202.h"
void func_004FABDC(En202* e, s32 a, s32 b, s32 c);
void En202::f() {
    m3dc.x = 0.0f;
    m3dc.y = 0.0f;
    m3dc.z = 0.0f;
    func_004FABDC(this, 0, -1, 0);
    m59c.set(0x300);
    func_00150A84(this, sead::SafeString("SE_BigIceGimos_MOVE_START"), 0);
}
