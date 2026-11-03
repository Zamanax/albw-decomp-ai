typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_0072623C;
extern TypeInfo data_00726240;
extern const char ro_006F5D5C[];
extern int func_00100174(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_0072623C & 1) && func_00100174(&data_0072623C)) {
        { TypeInfo* t = &data_00726240; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_0072623C);
    }
    return &data_00726240;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }
extern char* data_00706E20;
extern const u32 ro_006930E4;
typedef struct Mgr { u8 pad[0x3dbc0]; void* m3DBC0; } Mgr;
extern Obj** func_005841A8(Mgr* mgr, u32 k, void* p);
typedef struct A { Obj base; u8 pad[0x478 - 4]; u32 m478; } A;
extern void func_0023B228(A* a);
void func_0023A9A8(void)
{
    u32 k = ro_006930E4;
    Mgr* mgr = (Mgr*)data_00706E20;
    A* a = (A*)dynCast(*func_005841A8(mgr, k, mgr->m3DBC0));
    if (a) func_0023B228(a);
}
