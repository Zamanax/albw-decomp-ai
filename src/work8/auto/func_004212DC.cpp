#include "albw_types.h"
#include "vec3.h"
struct Bounds22 { Vec3 minimum, maximum; };
void target(Bounds22* p, const Vec3* v, u32 count) {
    p->minimum = *v;
    p->maximum = *v;
    for (u32 i = 1; i < count; ++i) {
        const Vec3& e = v[i];
        if (e.x < p->minimum.x) p->minimum.x = e.x;
        else p->maximum.x = e.x > p->maximum.x ? e.x : p->maximum.x;
        if (e.y < p->minimum.y) p->minimum.y = e.y;
        else p->maximum.y = e.y > p->maximum.y ? e.y : p->maximum.y;
        if (e.z < p->minimum.z) p->minimum.z = e.z;
        else p->maximum.z = e.z > p->maximum.z ? e.z : p->maximum.z;
    }
}
