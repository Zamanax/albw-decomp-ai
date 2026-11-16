#include "albw_types.h"
struct A45 { char pad[0x45]; u8 b45; };
struct B70 { char pad[0x70]; u8 f70; };
struct Obj { char pad0[0x1c]; struct B70* b1c; char pad20[0x44 - 0x20]; struct A45* a44; char pad48[0x4c - 0x48]; f32 f4c; u8 u50; };
extern u32 func_001B6CE4(struct Obj*);
u32 func_004215C8(struct Obj* p) {
    u32 r = func_001B6CE4(p);
    f32 t = p->f4c;
    if ((f32)p->u50 > t) {
        p->u50 = (u8)((u32)((f32)p->u50 - t));
        r = 0;
    } else {
        p->u50 = 0;
    }
    struct A45* a = p->a44;
    a->b45 = p->u50;
    struct B70* b = p->b1c;
    b->f70 = b->f70 | 2;
    return r;
}
