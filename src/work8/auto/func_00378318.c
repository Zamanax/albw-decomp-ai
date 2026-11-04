/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32; typedef int s32; typedef unsigned char u8;
typedef struct TypeInfo { const void* parent; } TypeInfo;
typedef struct Actor Actor;
typedef struct ActorVt {
    int (*checkDerived)(Actor* a, const TypeInfo* ti);
    char pad4[0x60 - 4];
    void (*m60)(Actor* a);
} ActorVt;
struct Actor { const ActorVt* vt; };
typedef struct Sub { char pad0[0x166]; u8 m166; } Sub;
typedef struct Sys { char pad0[0x18]; u32 m18; } Sys;
typedef struct Obj {
    const void* vt; char pad4[0x50 - 4]; Sub* m50; char pad54[0x74 - 0x54]; u32 m74;
} Obj;
extern char data_00706E20[];
extern u32 data_007260DC;
extern TypeInfo data_007260E0;
extern Sys* data_00708998;
extern const char ro_006F6314[];
extern const char ro_006E58E0[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
extern Actor* func_0052FBA0(u32 mgr, u32 h);
extern void func_001E8618(u32 v);
extern void func_002D5D3C(Obj* o);

static const TypeInfo* getTI(void)
{
    if (!(data_007260DC & 1) && __cxa_guard_acquire(&data_007260DC)) {
        { TypeInfo* t = &data_007260E0; t->parent = ro_006F6314; }
        __cxa_guard_release(&data_007260DC);
    }
    return &data_007260E0;
}

static int isDerived(Actor* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}

static void callM60(Actor* a)
{
    if (a != 0) a->vt->m60(a);
}

void func_00378318(Obj* o)
{
    Actor* a;
    o->vt = ro_006E58E0;
    a = func_0052FBA0((*(u32*)data_00706E20 + 0x3D800) + 0x3BC, o->m74);
    if (!isDerived(a)) a = 0;
    callM60(a);
    func_001E8618(data_00708998->m18);
    Sub* s = o->m50;
    s->m166 = 1;
    func_002D5D3C(o);
}
