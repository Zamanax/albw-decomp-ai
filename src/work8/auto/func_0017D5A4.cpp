#include "albw_types.h"
#include "vec3.h"

extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_0017B378(void* self, void* p, u32 a, u32 b);
extern "C" void func_0017B688(void* self);
extern "C" s32 func_0068C690(const Vec3& v);

extern "C" void func_0017D5A4(char* self) {
    Vec3 d(*func_00520FC0(self), *(Vec3*)(self + 0x3d0));
    void* arg = 0;
    s32 ang = func_0068C690(d);
    if (*(u32*)(self + 0x850) > 0x1e) {
        arg = &ang;
    }
    func_0017B378(self, arg, 1, 0);
    u32 lo = *(u32*)(self + 0x850);
    u32 hi = *(u32*)(self + 0x854);
    if (lo >= hi) {
        func_0017B688(self);
    } else {
        *(u32*)(self + 0x850) = lo + 1;
    }
}
