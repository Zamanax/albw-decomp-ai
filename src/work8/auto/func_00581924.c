typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00727620;
extern TypeInfo data_00727624;
extern const char ro_006F65E4[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; u8 pad[0x140 - 4]; void* m140; };
typedef struct Mgr { u8 pad[0x1c]; Obj* m1c; } Mgr;
extern Mgr* data_007165A0;
extern void* func_0057F260(void* p);
extern s32 func_0056D3E4(void* p, s32 b);

static const TypeInfo* getTI(void)
{
    if (!(data_00727620 & 1) && __cxa_guard_acquire(&data_00727620)) {
        { TypeInfo* t = &data_00727624; t->vt = ro_006F65E4; }
        __cxa_guard_release(&data_00727620);
    }
    return &data_00727624;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { if (isDerived(a)) return a; return 0; }

s32 func_00581924(void* self, s32 b)
{
    Obj* o = dynCast(data_007165A0->m1c);
    void* p = func_0057F260(o->m140);
    if (p == 0) return -1;
    return func_0056D3E4(p, b);
}
