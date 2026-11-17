#include "albw_types.h"
#include "vec3.h"

struct Ob208 {
    char p0[0xc8];
    Vec3 mc8;
    Vec3 md4;
    u32 me0;
    f32 me4;
    u32 me8;
    char pec[0x198 - 0xec];
    Vec3 m198;
    char p1a4[0x1b0 - 0x1a4];
    Vec3 m1b0;
    Vec3 m1bc;
    char p1c8[0x1cc - 0x1c8];
    Vec3 m1cc;
};
void func_001215C0(Ob208* o) {
    o->m1b0.setCopy(o->mc8);
    o->m1bc.setCopy(o->md4);
    f32 dz = o->m1b0.z - o->m1bc.z;
    f32 dy = o->m1b0.y - o->m1bc.y;
    f32 dx = o->m1b0.x - o->m1bc.x;
    f32 sq = dx * dx + dy * dy + dz * dz;
    o->me4 = sqrtf(sq);
    o->me8 = o->me0;
    o->m198.setCopy(o->m1cc);
}
