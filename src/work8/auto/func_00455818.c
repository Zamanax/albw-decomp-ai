typedef unsigned int u32;
typedef unsigned short u16;
typedef signed char s8;
struct Child { char a[4]; u32 w; char b[0xe]; u16 flags; };
struct S { char pad0[0x14]; struct Child* child; u32 f18; char pad1[0x50]; s8 f6c; char pad2[0x2f]; u32 f9c; u32 fa0; };
extern void func_00231448(void*);
extern void func_002C00A8(void*);

void func_00455818(struct S* p) {
    func_00231448((char*)p + 0x20);
    s8 t = p->f6c;
    if (t == 0) return;
    p->f18 &= ~4u;
    if (t == 2) {
        struct Child* c = p->child;
        u32 v = p->f9c;
        c->w = v;
        u32 b = v; if (b) b = 1;
        u16* fl = &c->flags;
        if (b) *fl |= 0x40; else *fl &= ~0x40;
        func_002C00A8(p->child);
        return;
    }
    if (t != 3) return;
    struct Child* c = p->child;
    u32 v = p->fa0;
    c->w = v;
    u32 b = v; if (b) b = 1;
    u16* fl = &c->flags;
    if (b) *fl |= 0x40; else *fl &= ~0x40;
    func_002C00A8(p->child);
}
