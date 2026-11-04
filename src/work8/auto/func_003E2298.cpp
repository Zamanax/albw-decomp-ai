
#include "vec3.h"

extern "C" void func_003E2298(Vec3* out, const Vec3* a, const Vec3* b) {
    Vec3 r;
    r.x = a->y * b->z - a->z * b->y;
    r.y = a->z * b->x - a->x * b->z;
    r.z = a->x * b->y - a->y * b->x;
    out->x = r.x; out->y = r.y; out->z = r.z;
}
