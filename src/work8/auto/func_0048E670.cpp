#include "albw_types.h"

struct Owner {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14(void* a);
    virtual void v15(void* a, u32 b);
    virtual void v16(void* a);
    virtual void v17(void* a);
    virtual void v18(void* a, void* b);
};

// Zeroed 16-byte local: u32 at +0, u64 at +8 (the strd).
struct Blk16 {
    u32 a;
    u64 b;
};

// 0x001E6CE8 is a `bx lr` no-op; the call below is linker-NOPed (mov r0, r0 at +0x28).
extern void func_001E6CE8(Owner*, void*, void*);

void func_0048E670(Owner* self, void* r1, u32* r2) {
    Blk16 t;
    t.a = 0;
    t.b = 0;
    func_001E6CE8(self, r1, &t);
    self->v14(r1);
    self->v16(r1);
    self->v17(r1);
    self->v15(r1, *r2);
    self->v18(r1, r2 + 2);
}
