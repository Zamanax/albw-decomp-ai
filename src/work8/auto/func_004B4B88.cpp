#include "sead_string.h"
extern "C" void* func_00689A2C(void* self, char* buf, s32 size);
extern "C" void func_00688CA0(void* self, void* dst);
extern "C" void func_006875AC(u32* out, void* s, s32 base);
extern "C" void func_004CDF40(void* mgr, s32 id, s32 set);
extern "C" const char ro_006F6B18[];
extern "C" const char ro_006F5B58[];
extern void* data_0070B728;

struct Buf10 {
    void* vptr;
    char* top;
    s32 size;
    char mBuf[10];
};

extern "C" void func_004B4B88(void* a0, void* a1, void* a2) {
    Buf10 s;
    Buf10* t1 = &s;
    void * t0 = func_00689A2C(t1, t1->mBuf, 10);
    Buf10* t = (Buf10*)t0;
    t->vptr = (void*)ro_006F6B18;
    t->top[0] = 0;
    t->vptr = (void*)ro_006F5B58;
    func_00688CA0(a2, &s);
    u32 v = 0;
    func_006875AC(&v, &s, -1);
    func_004CDF40(data_0070B728, (u16)v, 1);
}
