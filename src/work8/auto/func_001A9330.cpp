#include "albw_types.h"
#include "flags.h"

struct V3_9A330 { f32 x, y, z; };

struct Obj9A330 {
    char pad0[0x3d0];
    V3_9A330 m3D0;
    V3_9A330 m3DC;
    char pad3e8[0x59c - 0x3e8];
    BitFlag32 m59C;
    char pad5a0[0x8bc - 0x5a0];
    s32 m8BC;
    char pad8c0[0x91c - 0x8c0];
    f32 m91C;
};

extern bool func_0058A8F0(Obj9A330*);
extern __attribute__((notailcall)) void func_0065A984(u32*, s32);
extern void func_00115C54(V3_9A330*, const V3_9A330*, const V3_9A330*);

extern "C" void func_001A9330(Obj9A330* self) {
    if (self->m8BC > 0x14) {
        f32* q = &self->m91C;
        f32 v = *q;
        f32 d = 0.01f - v;
        *q = v + d * 0.1f;
        self->m59C.reset(0x80);
        self->m59C.reset(4);
    }
    if (func_0058A8F0(self)) {
        func_0065A984((u32*)&self->m8BC, 0);
        return;
    }
    V3_9A330* out = &self->m3D0;
    func_00115C54(out, out, &self->m3DC);
}
