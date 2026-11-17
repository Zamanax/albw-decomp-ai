#include "albw_types.h"
#include "vec3.h"

extern "C" Vec3* func_00520FC0(void*);
extern "C" s32 func_004904CC(f32, f32);
extern "C" void func_004D8054(void*, s32, f32);

extern "C" void func_00313224(u8* self) {
    void (*fp)(u8*, u32, s32) = *(void (**)(u8*, u32, s32))(*(u8**)self + 0xac);
    fp(self, 0, -1);
    Vec3* dst = (Vec3*)(self + 0xa14);
    *dst = *(Vec3*)(self + 0x3d0);
    Vec3 d = *func_00520FC0(self) - *(Vec3*)(self + 0x3d0);
    s32 a = func_004904CC(d.x, d.z);
    func_004D8054(dst, a, -0.25f);
    *(f32*)(self + 0x834) = 0.01f;
    *(u16*)(self + 0xa30) = 0x78;
}
