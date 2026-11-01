#define OBJ1D6_EXTRA void func_00288090();
#include "../../work5/agent4/obj1d6.h"
extern "C" const Vec3& func_00559B54(void* self);
extern "C" void func_0037C574(void* self, s32 a);
static inline void setTimer(Timer* t, u32 n, u32 c) {
    t->max = n;
    if (n) t->rate = 1.0f / n;
    else t->rate = 0.0f;
    t->cur = c;
}
void Obj1D6::func_00288090() {
    m3dc.set(func_00559B54(this));
    if (*(u8*)((char*)this + 0x518))
        func_0037C574(this, 0x320);
    setTimer((Timer*)((char*)this + 0x534), 3, 0);
}
