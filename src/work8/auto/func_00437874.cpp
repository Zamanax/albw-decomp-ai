#include "vec3.h"
extern "C" bool func_0068A3EC(Vec3*, float);
bool target(Vec3* p, const Vec3* c, float r) {
    Vec3 d(*p, *c);
    d.y = 0.0f;
    if (sqrtf(d.x * d.x + d.z * d.z) > r) {
        func_0068A3EC(&d, r);
        const Vec3& dr = d;
        Vec3* pp = p;
        pp->setAdd(dr, *c);
        return true;
    }
    return false;
}
