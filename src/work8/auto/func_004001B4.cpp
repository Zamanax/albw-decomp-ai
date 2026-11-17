#include "albw_types.h"
#include "sead_math.h"

extern "C" void func_001119F4(void* dst, const void* src);

struct Owner {
    u8 pad0[0x0c];
    u32 m0c;
    u8 pad10[0x44 - 0x10];
    u8 m44;
    u8 pad45[0x48 - 0x45];
    Mtx34 m48;
    u32 m78;
    u32 m7c;
};

struct IdentHolder {
    Mtx34 m;
    IdentHolder() {
        m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
        m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
        m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f; m.m[2][3] = 0.0f;
    }
};

extern "C" void func_004001B4(Owner* o)
{
    u32 z = 0;
    o->m0c = z;
    o->m44 = (u8)z;
    o->m7c = z;
    static IdentHolder ident;
    func_001119F4(&o->m48, &ident.m);
    o->m78 = z;
}
