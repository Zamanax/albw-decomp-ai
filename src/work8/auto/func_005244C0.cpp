#include "albw_types.h"
#include "vec3.h"

extern char* data_0070FB60;
s32 func_0068C690(const Vec3* v);
u32 func_0054E228(void* self, u32 a);

typedef Vec3* (*VFn78)(void*);

extern "C" u32 func_005244C0(void* self, u32 a) {
    char* obj = data_0070FB60;
    u32 v = **(u32**)(obj + 0x24);
    if (((v + 0x20000000) >> 30) != 2) {
        return 0;
    }
    Vec3* src = *(Vec3**)(obj + 0x1c);
    Vec3 tmp = *src - *(*(VFn78*)(*(char**)self + 0x78))(self);
    s32 ang = func_0068C690(&tmp);
    if (((u32)(ang + 0x20000000) >> 30) != 0) {
        return 0;
    }
    return func_0054E228(self, a);
}
