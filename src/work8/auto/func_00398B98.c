/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_007279C0;
extern TypeInfo data_007279C4;
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
    if (!(data_007279C0 & 1) && __cxa_guard_acquire(&data_007279C0)) {
        { TypeInfo* t = &data_007279C4; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_007279C0);
    }
    return &data_007279C4;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }

extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern void func_00510288(unsigned);
extern void func_00668424(unsigned, unsigned);

void func_00398B98(unsigned a0)
{
    Obj *a;
    unsigned h = *(unsigned *)(a0 + 0x38);
    a = (Obj *)func_0052FBA0((*(unsigned *)data_00706E20 + 0x3D800) + 0x3BC, h);
    a = dynCast(a);
    if (a != 0) func_00510288((unsigned)a);
    func_00668424(a0 + 0x10, 0);
}
