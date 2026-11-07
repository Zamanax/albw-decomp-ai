/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;
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
extern void func_002F8DE4(void* self, s32 a, s32 b, s32 c);
extern s32 func_0018EC1C(void* self, u32 h);
extern void func_0065AF54(void* p, s32 v);
typedef struct Self {
    u8 pad0[0x2cc];
    u32 m2CC;
    u8 pad1[0x3dc - 0x2d0];
    float f3DC;
    float f3E0;
    float f3E4;
    u8 pad2[0x90c - 0x3e8];
    u8 m90C[0xa18 - 0x90c];
    u32 mA18;
} Self;
void func_001B0C48(Self* self)
{
    Obj* a;
    func_002F8DE4(self, 0xe, 0, 0);
    self->f3DC = 0.0f;
    self->f3E0 = 0.0f;
    self->f3E4 = 0.0f;
    a = dynCast(func_0052FBA0(data_00706E20 + 0x3dbbc, self->mA18));
    if (a == 0 || !func_0018EC1C(a, self->m2CC)) func_0065AF54(self->m90C, 9);
}
