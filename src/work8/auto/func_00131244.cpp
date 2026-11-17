#include "albw_types.h"
struct This131 { char pad0[0x2b5a]; u8 m2b5a; char pad1[0x2b62 - 0x2b5b]; u8 m2b62; };
struct Dst131 { u32 w0; u32 w4; char pad0[0x48]; u32 w50; u32 w54; };

void func_00115108(void*, u32, u32);
void func_001150CC(void*, u32, u32);

void* func_00131244(This131* t, Dst131* d, u32 x, u32 y) {
    u32* p = (u32*)((char*)d + 8);
    d->w0 = t->m2b62 | 0x80000000;
    d->w4 = 0xf02c0;
    func_00115108(p, y, 0xff02c1);
    p = (u32*)((char*)p + 0x48);
    *p = t->m2b5a | 0x80000000;
    p = p + 1;
    *p = 0xf02c0;
    p = p + 1;
    func_001150CC(p, x, 0xbf02c1);
    return (char*)p + 0x38;
}
