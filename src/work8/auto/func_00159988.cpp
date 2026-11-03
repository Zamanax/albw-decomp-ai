#define EN_EXTRA void f();
#define CLASS_A
#include "../../work7/opus/OP29/en213.h"
void En::f() {
    m59c.reset(4);
    m59c.reset(0x80);
    m970.rate = 0.0f;
    func_004FABDC(this, 1, -1, 0);
    m59c.reset(1);
    m59c.reset(2);
    m8e0.func_003C26B8();
    m8e0.func_003C2630();
    m95c.start(randU32(func_0058A7D4(this), 60) + 60);
}
