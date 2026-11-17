#include "albw_types.h"
#include "vec3.h"

extern char data_00708998[];
extern Vec3* func_00520FC0(char* self);
extern void func_001E8440(u32 a, Vec3* b, u32 c);
extern void func_004F68AC(char* self, u32 a1);

void func_00267404(char* self, u32 a1) {
    s8 t = *(s8*)(self + 0x8cc);
    if (t != 0xf && t != 0x11) {
        if (t != 0x12 && t != 0x14) {
            Vec3 d;
            Vec3* o = &d;
            Vec3* a = (Vec3*)(self + 0x3d0);
            o->setAdd(*a, *func_00520FC0(self));
            Vec3* r = &d;
            r->setMul(*r, 0.5f);
            func_001E8440(*(u32*)(*(u32*)data_00708998 + 0x18), &d, 1);
        }
    }
    func_004F68AC(self, a1);
}
