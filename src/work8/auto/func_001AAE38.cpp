#include "../../work7/ds2/ds2.h"
extern void func_0065AAC8(void*, int);
extern void func_004F4A68(void*, void*);
struct V3 { f32 x; f32 y; f32 z; };
struct Arg1AAE38 { char pad[4]; V3 v; };
struct Obj1AAE38 {
    char pad0[0x374];
    V3 m374;
    char pad380[0x908 - 0x380];
    u8 m908;
    char pad909[0x940 - 0x909];
    u32 m940;
    char pad944[0x964 - 0x944];
    u8 m964;
};
union Bits1AAE38 { f32 f; u32 i; };
void func_001AAE38(Obj1AAE38* self, Arg1AAE38* a) {
    if (self->m908 == 2) {
        V3* pv = &self->m374;
        f32 d = pv->x * a->v.x + pv->y * a->v.y + pv->z * a->v.z;
        Bits1AAE38 b;
        b.f = d;
        if (b.i > 0xbf19999a) {
            self->m964 = 1;
            self->m940++;
            func_0065AAC8((char*)self + 0x904, 1);
        }
    }
    func_004F4A68(self, a);
}
