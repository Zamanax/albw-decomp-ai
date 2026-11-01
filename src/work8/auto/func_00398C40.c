
/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_007279C0;
extern TypeInfo data_007279C4;
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
    if (!(data_007279C0 & 1) && __cxa_guard_acquire(&data_007279C0)) {
        { TypeInfo* t = &data_007279C4; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_007279C0);
    }
    return &data_007279C4;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { if (isDerived(a)) return a; return 0; }


extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern unsigned func_00510388(unsigned);
unsigned func_00398C40(unsigned a0)
{
  unsigned r4, t, h;
  t = *(unsigned *)((char *)a0 + 4);
  t = *(unsigned *)((char *)t + 0x8DC);
  t = *(unsigned *)((char *)t + 0x14);
  t = *(unsigned *)((char *)t + 8);
  if (t != 0x41200000) {
    return a0;
  }
  h = *(unsigned *)((char *)a0 + 0x38);
  r4 = (unsigned)dynCast((Obj*)func_0052FBA0((*(unsigned *)((char *)data_00706E20) + 0x3D800) + 0x3BC, h));
  if (r4 != 0) {
    return func_00510388(r4);
  }
  return r4;
}
