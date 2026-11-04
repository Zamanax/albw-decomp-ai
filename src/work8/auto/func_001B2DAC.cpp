#define EN_EXTRA void f();
#include "../../work5/agent9/en202.h"
void func_004FABDC(En202* e, s32 a, s32 b, s32 c);
void func_004FB4E0(En202* e, f32 r);
void En202::f() {
    func_004FABDC(this, 9, 0, 0);
    func_004FB4E0(this, 1.0f);
    m59c.set(0x4000);
    func_00150A84(this, "SE_Stalfos_WAKE_UP", 0);
}
