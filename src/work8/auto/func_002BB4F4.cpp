#include "albw_types.h"
struct En210;
struct StateMgr { void changeState(int s); };

#include "timer.h"


#include "flags.h"

void func_004F87F8(En210* e, s32 a);
bool func_0058A8F0(En210* e);
struct En210 {
    char p0[0x4f8];
    f32 m4f8;
    char p4fc[0x59c - 0x4fc];
    BitFlag32 m59c;
    char p5a0[0x8bc - 0x5a0];
    StateMgr mState;
    char p8bd[0x900 - 0x8bd];
    Timer m900;
    void f();
};
void En210::f() {
    {
        u32 c0 = m900.cur;
        u32 mx = m900.max;
        if (c0 < mx) {
            u32 n = c0 + 1;
            m900.cur = n;
            if (n != 0) {
                m59c.set(0x30);
                func_004F87F8(this, 0);
            }
        }
    }
    f32 v = (f32)m900.cur * 0.1f;
    if (m900.cur >= m900.max || v > 1.0f) v = 1.0f;
    m4f8 = v;
    if (func_0058A8F0(this)) mState.changeState(2);
}
