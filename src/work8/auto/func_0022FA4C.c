typedef unsigned int u32;
typedef unsigned char u8;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_007278B8;
extern TypeInfo data_007278BC;
extern const char ro_006F6080[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_007278B8 & 1) && __cxa_guard_acquire(&data_007278B8)) {
        { TypeInfo* t = &data_007278BC; t->vt = ro_006F6080; }
        __cxa_guard_release(&data_007278B8);
    }
    return &data_007278BC;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }
extern char* data_00706E20;
extern Obj* func_0052FBA0(void* mgr, u32 h);
extern void func_001D4AD8(Obj* a);
typedef struct Self { u8 pad[0x278]; u32 m278; } Self;
int func_0022FA4C(Self* self, u32 flag)
{
    if (flag != 0) return 1;
    Obj* a = func_0052FBA0(data_00706E20 + 0x3dbbc, self->m278);
    if (a != 0) {
        a = dynCast(a);
    }
    if (a != 0) func_001D4AD8(a);
    return 1;
}
