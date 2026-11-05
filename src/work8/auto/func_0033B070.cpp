#include "vec3.h"

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct SP {
 SP():m1c(0),m20(0),m24(0),m48(0),m4c(0),m2c0(0){func_002DFF7C();}
 void func_002DFF7C();
 u32 m0; Vec3 m4; f32 m10[3]; u32 m1c, m20, m24;
 u16 m28, m2a, m2c, m2e;
 char p30[0x44 - 0x30];
 f32 m44; u32 m48, m4c; u16 m50;
 char p52[0x2c0 - 0x52];
 u32 m2c0;
};
extern const s32 ro_006931B0;
u32 func_0019B04C(s32);
struct Game;
extern Game* data_00706E20;
void func_004C43E0(Game*, const SP&);

u32 func_0033B070(const Vec3* a0, u32 a1, u32 a2) {
 f32 x = a0->x;
 f32 y = a0->y;
 f32 z = a0->z;
 x = x + 0.2f;
 y = y + 0.2f;
 SP p;
 p.m0 = func_0019B04C(ro_006931B0);
 p.m10[0] = 1.0f;
 p.m10[1] = 1.0f;
 p.m10[2] = 1.0f;
 p.m20 = a1;
 p.m4 = Vec3(x, y, z);
 p.m28 = (u16)a2;
 p.m2a = 1;
 func_004C43E0(data_00706E20, p);
 return 0;
}
