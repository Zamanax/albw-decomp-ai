/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_007266A8;
extern TypeInfo data_007266AC;
extern const char ro_006F6500[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_007266A8 & 1) && __cxa_guard_acquire(&data_007266A8)) {
        { TypeInfo* t = &data_007266AC; t->vt = ro_006F6500; }
        __cxa_guard_release(&data_007266A8);
    }
    return &data_007266AC;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }

static void orFlag(unsigned a0, unsigned m) { *(unsigned *)(a0 + 0x59C) |= m; }
extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern void func_002A9934(unsigned);
void func_00125FE4(unsigned a0)
{
    Obj *a;
    unsigned id;
    orFlag(a0, 0x1000);
    id = *(unsigned *)(a0 + 0x8E0);
    a = (Obj *)func_0052FBA0((*(unsigned *)((char *)data_00706E20) + 0x3D800) + 0x3BC, id);
    if (a != 0) {
        a = dynCast(a);
    }
    if (a != 0) func_002A9934((unsigned)a);
}
