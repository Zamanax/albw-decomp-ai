/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32; typedef int s32; typedef unsigned char u8;
struct TypeInfo { const void* vt; };
struct Obj;
struct ObjVt { s32 (*checkDerived)(Obj*, const TypeInfo*); };
struct Obj {
    const ObjVt* vt;
    u8 pad[0x390 - 4];
    u8 m390;
    u8 m391;
};
extern "C" u32 data_007276C0;
extern "C" TypeInfo data_007276C4;
extern "C" const char ro_006F6644[];
extern "C" int __cxa_guard_acquire(u32* g);
extern "C" void __cxa_guard_release(u32* g);

static const TypeInfo* getTI(void)
{
    if (!(data_007276C0 & 1) && __cxa_guard_acquire(&data_007276C0)) {
        TypeInfo* t = &data_007276C4; t->vt = ro_006F6644;
        __cxa_guard_release(&data_007276C0);
    }
    return &data_007276C4;
}
static Obj* dynCast(Obj* a)
{
    const TypeInfo* ti = getTI();
    return (a && a->vt->checkDerived(a, ti)) ? a : 0;
}

struct Self {
    u8 pad[0x20]; Obj* m20; u8 pad1[0x11c - 0x24]; s32 m11c; s32 m120;
    s32 func_0057F3D0(u32 k);
};
s32 Self::func_0057F3D0(u32 k)
{
    switch (k) {
    case 2: {
        Obj* p = dynCast(m20);
        if (p->m390 == 0) return m11c;
        return m120;
    }
    case 3:
    case 4: {
        Obj* p = dynCast(m20);
        if (p->m391) return m120;
        return m11c;
    }
    case 5:
    case 6:
    case 7:
        return m11c;
    case 8:
    case 9:
    case 10:
        return m120;
    default:
        return 0;
    }
}
