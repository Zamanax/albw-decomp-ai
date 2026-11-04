typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef float f32;


#include "vec3.h"

struct SpawnParam;
void func_002DFF7C(SpawnParam* p);

struct SpawnParam {
    SpawnParam() : m1c(0), m20(0), m24(0), m48(0), m4c(0), m2c0(0) { func_002DFF7C(this); }
    u32 m0;
    Vec3 m4;
    Vec3 m10;
    u32 m1c;
    u32 m20;
    u32 m24;
    u16 m28, m2a, m2c, m2e;
    char p30[0x44 - 0x30];
    f32 m44;
    u32 m48, m4c;
    u16 m50;
    char p52[0x2c0 - 0x52];
    u32 m2c0;
};

u32 func_0019B04C(u32);
extern u32 ro_0069325C;
extern void* data_00706E20;
void func_004C43E0(void*, const SpawnParam*);

void func_00512EE4(const Vec3* pos, const Vec3* v, u32 arg) {
    SpawnParam p;
    p.m0 = func_0019B04C(ro_0069325C);
    p.m4c = arg;
    p.m4 = *pos;
    p.m10 = *v;
    p.m4.y = pos->y;
    p.m2a = 9;
    p.m2e = 1;
    func_004C43E0(data_00706E20, &p);
}
