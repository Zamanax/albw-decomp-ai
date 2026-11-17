#include "albw_types.h"
#include "vec3.h"
extern "C" void func_00115C54(Vec3*, const Vec3&, const Vec3&);

extern "C" void func_001512B4(char* self, const Vec3* a) {
    char* r = *(char**)(self + 0x1c);
    Vec3 t = *a + *(const Vec3*)(self + 4);
    Vec3* d = (Vec3*)(r + 0x88);
    d->set(t);
    *(u8*)(r + 0xa0) = 1;
}
