typedef signed int s32;
typedef float f32;
#include "vec3.h"
struct Obj { unsigned char pad[0x3d0]; Vec3 pos; unsigned char pad2[0x494 - 0x3dc]; unsigned char m494; };
extern "C" Vec3* func_00520FC0(Obj*);
static inline f32 dist2(const Vec3* a, const Vec3& b){
  f32 dx = a->x - b.x;
  f32 dy = a->y - b.y;
  f32 dz = a->z - b.z;
  return dx * dx + dy * dy + dz * dz;
}

s32 func_0052AD58(Obj* self, void* a1){
  if (self->m494) return 0;
  Vec3* s = (Vec3*)((char*)self + 0x3d0);
  f32 d2 = dist2(s, *func_00520FC0(self));
  if (d2 < 0.8f) return 2;
  return 0;
}
