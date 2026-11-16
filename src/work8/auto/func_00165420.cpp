#include "albw_types.h"
#include "vec3.h"
extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_0068C690(const Vec3& v);
void func_00165420(void* self, u32 kind) {
    u32 k = kind & 0xff;
    if (k == 0x1e || k - 0xe <= 3) {
        Vec3 d;
        Vec3* out = &d;
        const Vec3* p = func_00520FC0(self);
        func_00115C70(out, p, (const Vec3*)((char*)self + 0x3d0));
        s32* ang = (s32*)((char*)self + 0x3e8);
        *ang = func_0068C690(d);
    }
}
