#include "albw_types.h"
#include "vec3.h"

struct S {
    Vec3 min;
    Vec3 max;
    f32 a;
    u32 b;
    f32 c;
};

void func_002E1588(S* p) {
    p->min.x = 3.402823466e38f;
    p->min.y = 3.402823466e38f;
    p->min.z = 3.402823466e38f;
    p->max.x = -3.402823466e38f;
    p->max.y = -3.402823466e38f;
    S * t0 = p;
    t0->max.z = -3.402823466e38f;
    t0->b = 0;
    t0->a = 0.0f;
    t0->c = 0.0f;
}
