#include "../../../shared/include/albw_types.h"
struct Mgr { virtual void v0(); virtual void v1(); virtual u32 invoke(u32, u32, u32, u32); };
struct Self { char pad0[0x18]; Mgr* mgr; };
u32 func_00408FD0(Self* self, u32 a, u32 b, u32 c) {
    Mgr* m = self->mgr;
    u32 aa = a;
    if (m) return m->invoke((u32)self, aa, b, c);
    return 0;
}
