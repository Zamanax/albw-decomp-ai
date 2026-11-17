#include "albw_types.h"
#include "vec3.h"

extern void* data_0070FB60;

u32 func_0058D200(void* self) {
    u32 ret;
    if (*((u8*)self + 0x548) == 0) {
        void* singleton = data_0070FB60;
        const Vec3* pb = *(const Vec3**)((char*)singleton + 0x1c);
        const Vec3* pa = (const Vec3*)((char*)self + 0x3d0);
        Vec3 d = *pa - *pb;
        ret = 0x1b;
    } else {
        ret = 0;
    }
    return ret;
}
