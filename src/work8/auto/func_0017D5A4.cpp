#include "vec3.h"
#include "albw_types.h"

extern "C" Vec3* func_00520FC0(void*);
extern "C" void func_00115C70(Vec3*, const Vec3&, const Vec3&);
extern "C" s32 func_0068C690(const Vec3&);
extern "C" void func_0017B378(void*, s32*, u32, u32);
extern "C" void func_0017B688(void*);

struct SlotPair {
    u32 cur;
    u32 end;
};

extern "C" void func_0017D5A4(char* self) {
    Vec3 d;
    Vec3* out = &d;
    Vec3* p = func_00520FC0(self);
    func_00115C70(out, *p, *(Vec3*)(self + 0x3d0));
    s32* a = 0;
    s32 ang = func_0068C690(d);
    if (*(u32*)(self + 0x850) > 0x1e) {
        a = &ang;
    }
    func_0017B378(self, a, 1, 0);
    SlotPair pr = *(SlotPair*)(self + 0x850);
    if (pr.cur < pr.end) {
        *(u32*)(self + 0x850) = pr.cur + 1;
    } else {
        func_0017B688(self);
    }
}
