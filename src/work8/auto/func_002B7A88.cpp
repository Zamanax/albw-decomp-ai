#include "albw_types.h"
#include "vec3.h"

s32 func_0068C690(const Vec3* v);
struct G70FB60 { char _0[0x1c]; Vec3* m1C; };
extern G70FB60* data_0070FB60;
struct Obj2B7A88 { u8 pad0[0x3d0]; Vec3 m3d0; u8 pad1[0x55a]; u8 m936; u8 pad2[0xa20 - 0x937]; s32 ma20; };

void func_002B7A88(Obj2B7A88* p) {
    if (p->m936 == 1) {
        Vec3 d(*data_0070FB60->m1C, p->m3d0);
        p->ma20 = func_0068C690(&d);
    }
}
