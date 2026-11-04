/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00726ED0;
extern TypeInfo data_00726ED4;
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
    if (!(data_00726ED0 & 1) && __cxa_guard_acquire(&data_00726ED0)) {
        { TypeInfo* t = &data_00726ED4; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_00726ED0);
    }
    return &data_00726ED4;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { if (isDerived(a)) return a; return 0; }
extern char* data_00706E20;
extern u32 data_0070C3C8;
typedef struct Mgr { u8 pad[0x3dbc0]; void* m3DBC0; } Mgr;
extern Obj** func_005841A8(Mgr* mgr, u32 k, void* p);
extern float func_00521238(void* self);
extern void func_0065BF44(void* p, s32 v);
extern void func_00391558(void);
typedef struct CounterPair { u32 cur, max; } CounterPair;
typedef struct Self {
    u8 pad0[0x414];
    u8 m414[4];
    u8 pad418[0x438 - 0x418];
    CounterPair timer;
    u8 pad440[0x447 - 0x440];
    u8 m447;
} Self;
u32 func_001C73CC(Self* self)
{
    CounterPair t = self->timer;
    if (t.cur < t.max) {
        u32 n = t.cur + 1;
        self->timer.cur = n;
        return n;
    }
    if (func_00521238(self) > 1.0f) {
        func_0065BF44(self->m414, 3);
    }
    if (self->m447 != 0) return self->m447;
    {
        Self* s = self;
        u32 k = data_0070C3C8;
        Mgr* mgr = (Mgr*)data_00706E20;
        u32 r = (u32)dynCast(*func_005841A8(mgr, k, mgr->m3DBC0));
        if (r != 0) {
            func_00391558();
            s->m447 = 1;
            return 1;
        }
        return r;
    }
}
