/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00725E1C;
extern TypeInfo data_00725E20;
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
    if (!(data_00725E1C & 1) && __cxa_guard_acquire(&data_00725E1C)) {
        { TypeInfo* t = &data_00725E20; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_00725E1C);
    }
    return &data_00725E20;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }
extern char* data_00706E20;
extern Obj* func_0052FBA0(void* mgr, u32 h);
extern int func_0018E508(Obj* a);
typedef struct Ref { u8 k0; u8 k1; } Ref;
typedef struct Msg { u8 pad[0x28]; u32 h; Ref* r; } Msg;
int func_004FA8A0(Msg* self)
{
    if (self->r == 0 || self->r->k1 != 9) return 0;
    Obj* a = func_0052FBA0(data_00706E20 + 0x3dbbc, self->h);
    if (a != 0) {
        a = dynCast(a);
        if (a != 0) { if (func_0018E508(a) != 0) return 1; }
    }
    return 0;
}
