#include "albw_types.h"

struct Req5C { u8 raw[0x5c]; };

extern "C" Req5C* func_002C11E8(Req5C*, u32, u32, bool);
extern "C" void func_0016898C(void*, Req5C*);
extern "C" void func_001692F8(void*, Req5C*);

struct Obj {
    u8 _00[0x0c];
    void* m0c;
    u8 _10[0x20];
    u8 m30;
    u8 _31[0x13];
    void* m44;
    u8 _48[0xc8];
    u32 m110;
    u8 _114[8];
    u8 m11c;
};

extern "C" void func_004F0864(Obj* self, u32 id, bool flag) {
    Req5C req;
    u16 uid = (u16)id;
    u32 arg = flag;
    void* m44 = self->m44;
    u32 one = 1;
    if (m44 != 0) {
        u8* hi = (u8*)self + 0x100;
        if (self->m110 & (one << uid)) {
            Req5C* r = func_002C11E8(&req, uid, arg, false);
            func_0016898C(self->m44, r);
            u8 old = hi[0x1c];
            self->m11c = one;
            if (old == 0) arg = 0;
        } else {
            func_002C11E8(&req, (u32)-1, 10, false);
            func_001692F8(m44, &req);
            u8 old = hi[0x1c];
            if (old != 0) arg = 0;
            self->m11c = 0;
        }
    }
    self->m30 = one;
    u32 a2 = arg;
    Req5C* r2 = func_002C11E8(&req, (u16)id, a2, false);
    func_0016898C(self->m0c, r2);
}
