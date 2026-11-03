/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00726698;
extern TypeInfo data_0072669C;
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
    if (!(data_00726698 & 1) && __cxa_guard_acquire(&data_00726698)) {
        { TypeInfo* t = &data_0072669C; t->vt = ro_006F6500; }
        __cxa_guard_release(&data_00726698);
    }
    return &data_0072669C;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
extern char* data_00706E20;
extern Obj* func_0052FBA0(void* mgr, u32 h);
typedef struct Rec { u8 pad[0x50]; u32 h; } Rec;
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }
Obj* func_002A90E8(Rec* self)
{
    Obj* a = func_0052FBA0(data_00706E20 + 0x3dbbc, self->h);
    if (a != 0) return dynCast(a);
    return 0;
}
