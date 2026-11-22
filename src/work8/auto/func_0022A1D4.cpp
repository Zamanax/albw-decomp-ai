#include "albw_types.h"
#include "vec3.h"

extern "C" void func_004FC07C(void* e, u32 a, u32 b, u32 c);
extern "C" s32 func_0068C690(const Vec3& v);
extern char* data_0070FB60;

extern "C" void func_0022A1D4(char* self) {
    *(f32*)(self + 0x3dc) = 0.0f;
    *(f32*)(self + 0x3e0) = 0.0f;
    *(f32*)(self + 0x3e4) = 0.0f;
    func_004FC07C(self, 4, 0xffffffffu, 0);
    u32 a = *(u32*)(self + 0xa7c);
    u32 b = *(u32*)(self + 0xa80);
    if (a < b) *(u32*)(self + 0xa7c) = a + 1;
    char* obj = data_0070FB60;
    u32* ss = (u32*)*(char**)(obj + 0x1c);
    u32* sd = (u32*)(self + 0xaf8);
    sd[0] = ss[0];
    sd[1] = ss[1];
    sd[2] = ss[2];
    Vec3 d = *(Vec3*)(self + 0xaf8) - *(Vec3*)(self + 0x3d0);
    *(s32*)(self + 0xab4) = func_0068C690(d);
}
