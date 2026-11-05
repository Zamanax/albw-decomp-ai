#include "albw_types.h"
#include "vec3.h"
#include "sead_math.h"
struct StateControl22 { u32 count; };
struct Tail22 {
 u8 pad0[0x3d0]; Vec3 pos3d0; f32 vx, vy, vz;
 u8 pad3e8[0x8cc-0x3e8]; f32 value8cc;
 u8 pad8d0[0x8d8-0x8d0]; u32 angle8d8;
 u32 angle8dc;
 u8 pad8e0[0x8e4-0x8e0]; u16 half8e4;
 u8 pad8e6[0x8f0-0x8e6]; StateControl22 state;
};
extern const SinCosSample ro_006C3AB8[];
extern "C" void func_004D8054(Vec3*, u32, f32);
extern "C" f32 func_004F944C();
extern "C" void func_0065DF0C(StateControl22*, s32);
extern "C" void func_003931EC(StateControl22*, s32);
extern "C" void func_0065DF78(StateControl22*);
inline f32 sinIdx(u32 a) {
 u32 idx = a >> 24;
 f32 frac = (a & 0xffffff) * (1.0f / 0x1000000);
 return ro_006C3AB8[idx].sin_val + ro_006C3AB8[idx].sin_delta * frac;
}
extern "C" void func_00654B58(Tail22* p) {
 u32& s = p->angle8dc;
 s += 0xAAAAAAA;
 u32 a = s;
 func_004D8054(&p->pos3d0, p->angle8d8, sinIdx(a) * p->value8cc);
 f32 zero = 0.0f;
 if (p->value8cc >= zero) {
  if ((s32)p->angle8dc > 0x40000000) p->value8cc = -p->value8cc;
  return;
 }
 if ((s32)p->angle8dc >= (s32)0xd5555556) return;
 p->half8e4 = 100;
 p->vy = func_004F944C();
 func_0065DF0C(&p->state, 0);
 func_003931EC(&p->state, 0);
 func_0065DF78(&p->state);
}
