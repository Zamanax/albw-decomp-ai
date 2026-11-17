#include "vec3.h"

// Linear interpolation: s + (a - s) * t.
Vec3 func_004997A0(const Vec3& s, const Vec3& a, float t) {
    Vec3 d = a - s;
    d *= t;
    return s + d;
}
