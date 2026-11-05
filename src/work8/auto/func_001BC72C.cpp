/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
#include "sead_rtti.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

extern "C" u32 data_00726AA8;
extern "C" TypeInfo data_00726AAC;
extern "C" const char ro_006F6500[];
extern "C" int __cxa_guard_acquire(u32* g);
extern "C" void __cxa_guard_release(u32* g);

struct Obj;
struct Obj { const ObjVt<Obj>* vt; };

static const TypeInfo* getTI(void)
{
    if (!(data_00726AA8 & 1) && __cxa_guard_acquire(&data_00726AA8)) {
        { TypeInfo* t = &data_00726AAC; t->vt = ro_006F6500; }
        __cxa_guard_release(&data_00726AA8);
    }
    return &data_00726AAC;
}

static int isDerived(Obj* a)
{
    const TypeInfo* ti = getTI();
    return a && a->vt->checkDerived(a, ti);
}
static Obj* dynCast(Obj* a) { return isDerived(a) ? a : 0; }

extern "C" char data_00706E20[];
extern "C" Obj* func_0052FBA0(void* mgr, u32 h);
extern "C" u32 func_005568E8(void* p);
extern "C" u32 func_00556A04(void* p);

struct Inner { u8 pad0[4]; float f4; };
struct Mid { u8 pad0[0x1c]; Inner* m1c; };
struct Holder { u8 pad0[8]; float f8; };
struct Self { u8 m0; u8 pad1[0x8c - 1]; Holder* m8c; };

extern "C" Mid* data_0070FB60;

extern "C" void func_001BC72C(Self* self, u32* h, s32 c)
{
    if (self->m0 != 0) return;
    if (c == 0) return;
    Mid* p = data_0070FB60;
    if (p != 0) {
        u32 key = func_005568E8(p);
        if (key == *h) {
            if (func_00556A04(p) != 0) { self->m0 = 2; return; }
            Holder* hd = self->m8c;
            Inner* in = p->m1c;
            float hv = hd->f8 + 0.5f;
            float d = in->f4 - hv;
            float ad = (d > 0.0f) ? d : -d;
            if (ad < 0.1f) self->m0 = 2;
            return;
        }
    }
    Obj* a = func_0052FBA0((char*)(*(char**)data_00706E20) + 0x3d800 + 0x3bc, *h);
    if (a != 0) a = dynCast(a);
    if (a != 0) self->m0 = 2;
}
