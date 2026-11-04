// 0x1E5B70: m3dc = (0, 0, z)
typedef float f32;

#include "vec3.h"

struct Obj1E5B70 {
    void setVelZ(f32 z);
    char pad[0x3dc];
    Vec3 m3dc;
};
void Obj1E5B70::setVelZ(f32 z) { m3dc = Vec3(0.0f, 0.0f, z); }
