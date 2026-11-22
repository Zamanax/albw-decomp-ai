typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
#include "sead_string.h"

extern "C" void* data_00709D28;
extern "C" const char ro_0069E8C0[];
extern "C" void func_004A9120(void*, void*);
extern "C" void func_004CF478(void*, bool, s32);
extern "C" void func_00151148(void*, s32);
extern "C" void func_0014DBF4(void*, const SafeString&, void*, s32);

struct Self {
    char _0[0x610];
    u32 m610;
    char _614[4];
    void** m618;
    char _61c[0xc];
    u32 m628;
};

struct P {
    u8 m0;
    char _1[9];
    u8 m0a;
    char _b[4];
    void* m10;
    void* m14;
};

void f(Self* self, P* p) {
    func_004A9120(data_00709D28, (char*)p + 0x48);
    self->m628 += 1;
    func_004CF478(p->m10, 0, 0);
    func_00151148(p->m14, 0);
    P * t0 = p;
    t0->m0 = 4;
    u32 idx = t0->m0a;
    u32 t2 = self->m610;
    void* o = (t2 > idx) ? self->m618[idx] : 0;
    void (*fp)(void*) = *(void (**)(void*))((*(char**)o) + 0x30);
    fp(o);
    func_0014DBF4(self, SafeString(ro_0069E8C0), 0x24 + (char*)t0, 0);
}
