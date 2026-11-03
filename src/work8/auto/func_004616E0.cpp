#include "../../../shared/include/albw_types.h"

// 16-bit flag word at object+0x16; assignment is a whole-word copy back.
struct BitFlag16 {
    u16 v;
    BitFlag16() {}
    BitFlag16(u16 x) : v(x) {}
    void set(u16 m) { *this = BitFlag16((u16)(v | m)); }
    void reset(u16 m) { *this = BitFlag16((u16)(v & ~m)); }
};

struct Child476 {
    u8 pad0[4];
    u32 f4;
    u8 pad8[0x16 - 8];
    BitFlag16 flags;
};

struct Owner476 {
    u8 pad[0x14];
    Child476* child;
    u32 w18;
    u8 pad1c[0x94 - 0x1c];
    u32 f94;
};

extern "C" void func_00232468(Owner476*);
extern "C" void func_002C00A8(Child476*);

void func_004616E0(Owner476* p)
{
    func_00232468(p);
    Child476* c = p->child;
    if (c) {
        u32 v = p->f94;
        c->f4 = v;
        u32 b = v;
        if (b)
            b = 1;
        u16* pf = &c->flags.v;
        u16 fl = *pf;
        if (b)
            fl |= 0x40;
        else
            fl &= (u16)~0x40;
        *pf = fl;
        func_002C00A8(p->child);
        Child476* c2 = p->child;
        BitFlag16* f2 = &c2->flags;
        f2->reset(2);
    }
}
