// 0x1D4948 MATCH: returns const Vec3& (callers use r0); reference local + inline set(const Vec3&){*this=o;}
typedef float f32;

#include "vec3.h"

struct A3 {
    char pad0[0x44c];
    Vec3 m44c;
    char pad458[4];
    Vec3 m45c;
    const Vec3& func_001D4948();
};
const Vec3& A3::func_001D4948() { Vec3& d = m45c; d.setCopy(m44c); return d; }
