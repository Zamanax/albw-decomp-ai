#define EN_EXTRA void f();
#include "../../work5/agent16/en213.h"
struct Rec8E0 { s32 a; s32 b; f32 c; };
void func_004F87F8(En* e, s32 a);
void En::f() {
    m3dc.set(0.0f, 0.0f, 0.0f);
    Rec8E0* r = (Rec8E0*)&m8e0;
    f32 k = 0.016666668f;
    r->b = 0x3c; r->c = k; r->a = 0;
    func_004FABDC(this, 2, 0, 0);
    func_004F87F8(this, 1);
}
