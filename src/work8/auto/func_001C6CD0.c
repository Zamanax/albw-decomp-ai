/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
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

extern char data_00706E20[];
extern char data_0070C3C8[];
extern unsigned func_005841A8(unsigned, unsigned, unsigned);
extern unsigned func_00391558(void);
typedef struct Eff { char pad[0x1c]; u32 m1c; } Eff;
typedef struct EffHandle { Eff* p; u32 id; } EffHandle;
typedef struct EffRet { Eff* p; u32 id; } EffRet;
extern void func_00110848(Eff* e);
extern EffRet func_004A1B9C(void* a, const char* name);
typedef struct Cls { char p0[0x344]; void* m344; char p348[0x448 - 0x348]; EffHandle mh; } Cls;

unsigned func_001C6CD0(Cls* self)
{
  unsigned r4, t3, t4, t5, t6, t7;
  const char* nm = "Land";
  EffHandle* h = &self->mh;
  if (self->m344 != 0) {
    Eff* p = h->p;
    if (p != 0) { u32 id = h->id; if (p->m1c == id) func_00110848(p); }
    { EffRet r = func_004A1B9C(self->m344, nm); h->p = r.p; h->id = r.id; }
  } else {
    h->p = 0;
    h->id = 0;
  }
  t3 = *(unsigned *)((char *)data_00706E20);
  t4 = *(unsigned *)((char *)data_0070C3C8);
  t5 = *(unsigned *)((char *)t3 + 0x3DBC0);
  t6 = func_005841A8(t3, t4, t5);
  t7 = *(unsigned *)((char *)t6);
  r4 = (unsigned)dynCast((Obj*)t7);
  if (r4 != 0) {
    return func_00391558();
  }
  return r4;
}
