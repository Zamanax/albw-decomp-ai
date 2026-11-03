/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_007278F0;
extern TypeInfo data_007278F4;
extern const char ro_006F5D5C[];
extern char* data_0070ADA8;
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
typedef struct Obj Obj;
typedef struct ObjVt {
    int (*checkDerived)(Obj* a, const TypeInfo* ti);
} ObjVt;
struct Obj { const ObjVt* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_007278F0 & 1) && __cxa_guard_acquire(&data_007278F0)) {
        { TypeInfo* t = &data_007278F4; t->vt = ro_006F5D5C; }
        __cxa_guard_release(&data_007278F0);
    }
    return &data_007278F4;
}
static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }
extern unsigned func_004FAE78(Obj* self, char* other, float f);
unsigned func_00120B58(Obj* a0, unsigned v)
{
    float f = (float)v;
    Obj* r4 = dynCast(a0);
    if (r4 != 0) {
        char* g = data_0070ADA8;
        if (g == 0) return func_004FAE78(r4, 0, f);
        if (g == (char*)r4) return (unsigned)r4;
        return func_004FAE78(r4, g + 0x3d0, f);
    }
    return (unsigned)r4;
}
