#include "vec3.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;

extern void* data_0070C8E0;
s32 func_00581D60(void* o);

extern "C" void* func_005582E8(u8* self) {
    if (*(s16*)(self + 0x18) >= 0) {
        s32 m = func_00581D60(data_0070C8E0);
        if (*(s16*)(self + 0x18) != m) {
            static Vec3 zero(0.0f, 0.0f, 0.0f);
            return &zero;
        }
    }
    return self + 0x28;
}
