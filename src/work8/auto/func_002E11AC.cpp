typedef unsigned int u32; typedef float f32;

#include "vec3.h"

struct Bounds22 { Vec3 minimum; Vec3 maximum; u32 unk18; u32 count; f32 value; };
inline f32 minimum22(f32 a, f32 b) { return a > b ? b : a; }
inline f32 maximum22(f32 a, f32 b) { return a > b ? a : b; }
inline void minimize22(f32& current, const f32& value) { current = current > value ? value : current; }
void func_002E11AC(Bounds22* p, const Vec3* v, u32 n, f32 f) {
    if (p->count != 0) {
        minimize22(p->minimum.x, v->x);
        p->minimum.y = minimum22(p->minimum.y, v->y);
        p->minimum.z = minimum22(p->minimum.z, v->z);
        p->maximum.x = maximum22(p->maximum.x, v->x);
        p->maximum.y = maximum22(p->maximum.y, v->y);
        p->maximum.z = maximum22(p->maximum.z, v->z);
    }
    else {
        Vec3& mn = p->minimum;
        mn.x = v->x; mn.y = v->y; mn.z = v->z;
        Vec3& mx = p->maximum;
        mx.x = v->x; mx.y = v->y; mx.z = v->z;
    }
    u32 c = p->count >= n ? p->count : n;
    f32 value = p->value < f ? f : p->value;
    p->count = c;
    p->value = value;
}
