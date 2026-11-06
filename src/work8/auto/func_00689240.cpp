#include "sead_string.h"

extern "C" void* func_0010CF28(u32 size);
extern "C" void* func_0048FB4C(void* self);
extern char ro_006C7C18[];

inline void* operator new(u32, void* p) { return p; }

struct Obj689240 {
    void* m0;                             // +0x00 vptr
    char _base[0x24 - 4];                 // +0x04 base fields (func_0048FB4C)
    sead::FixedSafeString<0x80> mStr;     // +0x24
};

void setvt(Obj689240* o, void* p) { o->m0 = p; }

Obj689240* func_00689240() {
    void* p = func_0010CF28(0xb4);
    if (p == 0) return 0;
    Obj689240* o = (Obj689240*)func_0048FB4C(p);
    sead::FixedSafeString<0x80>* s = &o->mStr;
    new (s) sead::FixedSafeString<0x80>();
    u8* q = (u8*)s;
    q[0x8c] = 7;
    q[0x8d] = 0xff;
    setvt(o, ro_006C7C18);
    return o;
}
