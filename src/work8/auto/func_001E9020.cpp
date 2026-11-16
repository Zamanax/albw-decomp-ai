typedef float f32;
typedef int s32;
#include "vec3.h"

s32 func_001E9020(const Vec3* a, const Vec3* b) {
    f32 az = a->z;
    f32 bz = b->z;
    if (az < bz) return -1;
    if (az == bz) {
        f32 ay = a->y;
        f32 by = b->y;
        if (ay < by) return -1;
        if (ay > by) return 1;
        return 0;
    }
    return 1;
}
