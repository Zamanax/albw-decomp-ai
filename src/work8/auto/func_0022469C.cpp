#include "vec3.h"

typedef unsigned char u8;
typedef unsigned int u32;

extern "C" void func_0036C42C(void*);
extern "C" Vec3 bss_0074D398;

extern "C" void func_0022469C(char* self) {
    Vec3* d = (Vec3*)(self + 0x400 + 0x304);
    {
        Vec3 t;
        t.setAdd(*(Vec3*)(self + 0x3d0), bss_0074D398);
        d->setCopy(t);
    }
    *(u8*)(self + 0x580) = 2;
    *(u32*)(self + 0x4b4) = (u32)d;
    func_0036C42C(self + 0x400 + 0x8c);
}
