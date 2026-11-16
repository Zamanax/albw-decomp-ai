#include "vec3.h"
#include "albw_types.h"
extern "C" void func_002ADE0C(void*, u32);
extern "C" void func_004FBCC0(void*);
extern "C" void func_002AD658(void*, s32, s32, s32, s32, s32);
extern const Vec3 data_007A9260;

extern "C" void func_002AE14C(void* self, u32 arg) {
    func_002ADE0C(self, arg);
    func_004FBCC0(*(void**)((char*)self + 0x34));
    u32* d = (u32*)((char*)self + 0x70);
    const u32* s = (const u32*)&data_007A9260;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    void* o = *(void**)((char*)self + 0x34);
    *(u32*)((char*)o + 0x500) = *(u32*)((char*)self + 0x174);
    func_002AD658(self, 0xd, (u8)arg, 0x1f, 0, 1);
}
