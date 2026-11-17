/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00725B24;
extern TypeInfo data_00725B28;
extern const char ro_006F5D5C[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_00725B24 & 1) && __cxa_guard_acquire(&data_00725B24)) {
        { TypeInfo* t = &data_00725B28; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_00725B24);
    }
    return &data_00725B28;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }

extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern void func_00147DA0(unsigned);
extern void func_00668BBC(unsigned, unsigned);

void func_003A3A18(unsigned a0)
{
    Obj *a;
    unsigned h = *(unsigned *)(a0 + 0x38);
    a = (Obj *)func_0052FBA0((*(unsigned *)data_00706E20 + 0x3D800) + 0x3BC, h);
    a = dynCast(a);
    if (a != 0) func_00147DA0((unsigned)a);
    func_00668BBC(a0 + 0x10, 0);
}
