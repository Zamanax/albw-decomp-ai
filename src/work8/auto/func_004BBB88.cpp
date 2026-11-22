#include "albw_types.h"
#include "vec3.h"
extern "C" int __cxa_guard_acquire(void*);
extern "C" void __cxa_guard_release(void*);
extern u32 data_0070C168;
extern Vec3 bss_0075C5D0;
extern char* data_0070FB60;

Vec3 func_004BBB88(char* self) {
    if (!(data_0070C168 & 1)) {
        if (__cxa_guard_acquire(&data_0070C168)) {
            Vec3* s = &bss_0075C5D0;
            s->x = 8.0f;
            s->y = 39.5f;
            s->z = -50.0f;
            __cxa_guard_release(&data_0070C168);
        }
    }
    char* q = *(char**)(data_0070FB60 + 0x1c);
    f32 a = *(f32*)q;
    u32 b = *(u32*)(q + 8);
    if (a < 11.0f && b > 0xc2280000u) {
        return bss_0075C5D0;
    }
    return *(Vec3*)(self + 8);
}
