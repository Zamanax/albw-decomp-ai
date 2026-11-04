typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

#include "vec3.h"

struct SP {
 SP():m1c(0),m20(0),m24(0),m48(0),m4c(0),m2c0(0){func_002DFF7C();}
 void func_002DFF7C();
 u32 m0; Vec3 m4; u32 m10[3]; u32 m1c, m20, m24;
 u16 m28, m2a, m2c, m2e;
 char p30[0x44 - 0x30];
 f32 m44; u32 m48, m4c; u16 m50;
 char p52[0x2c0 - 0x52];
 u32 m2c0;
};
extern const s32 ro_00693168;
u32 func_0019B04C(s32);
struct Global { u16 func_00581D60(); };
extern Global* data_0070C8E0;
struct Game;
extern Game* data_00706E20;
void func_004C43E0(Game*, const SP&);
void func_004E7460(const u32& x) {
 SP p;
 p.m0 = func_0019B04C(ro_00693168);
 p.m50 = data_0070C8E0->func_00581D60();
 p.m2a = 1;
 p.m2e = 1;
 p.m4c = x;
 func_004C43E0(data_00706E20, p);
}
