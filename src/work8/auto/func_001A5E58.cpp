#include "albw_types.h"
#include "vec3.h"
extern "C" s32 func_0058A474(void*, u32);
extern "C" void func_004D7F70(Vec3*, u32);

void func_001A5E58(char* self) {
    s32 r = func_0058A474(self, 0x32);
    u32 k = r ? 0x2aaaaaaa : 0xd5555555;
    Vec3 a(0.0f, 0.0f, 0.05f);
    u32 ang = *(u32*)(self + 0x940) + k;
    func_004D7F70(&a, ang);
    Vec3* d = (Vec3*)(self + 0x934);
    d->setCopy(a);
    *(f32*)(self + 0x938) = 0.5f;
    char* p = *(char**)(self + 0x900);
    p[0x24] = 0;
    self[0x904] = 2;
}
