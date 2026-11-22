#include "albw_types.h"
#include "vec3.h"

extern "C" void func_004D80A4(Vec3* out, u32 angle, f32 scale);
extern "C" s32 func_00145B68(Vec3* p, void* m);

extern "C" s32 func_0052EA80(char* self) {
    char* q = self + 0x300;
    Vec3 t;
    Vec3 u;
    Vec3 a;
    func_004D80A4(&a, *(u32*)(self + 0x3e8), 1.0f);
    a.y = -1.5f;
    Vec3 b;
    func_004D80A4(&b, *(u32*)(q + 0xe8), -1.0f);
    b.y = -1.5f;
    t = a + *(Vec3*)(self + 0x3d0);
    if (func_00145B68(&t, *(void**)(self + 0x624)) != 0) return 1;
    u = b + *(Vec3*)(self + 0x3d0);
    return func_00145B68(&u, *(void**)(self + 0x624)) != 0 ? 1 : 0;
}
