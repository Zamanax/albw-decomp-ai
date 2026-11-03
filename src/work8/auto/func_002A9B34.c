/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00725A04;
extern TypeInfo data_00725A08;
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
    if (!(data_00725A04 & 1) && __cxa_guard_acquire(&data_00725A04)) {
        { TypeInfo* t = &data_00725A08; t->vt = ro_006F6500; }
        __cxa_guard_release(&data_00725A04);
    }
    return &data_00725A08;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }

extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern void func_00125A6C(unsigned);
void func_002A9B34(unsigned a0)
{
    Obj *a;
    unsigned id;
    if (*(u8 *)(a0 + 0x8FF) == 0) return;
    id = *(unsigned *)(a0 + 0x8E0);
    a = (Obj *)func_0052FBA0((*(unsigned *)((char *)data_00706E20) + 0x3D800) + 0x3BC, id);
    if (a != 0) {
        a = dynCast(a);
    }
    if (a != 0) func_00125A6C((unsigned)a);
}
