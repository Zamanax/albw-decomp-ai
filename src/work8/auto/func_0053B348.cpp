#include "vec3.h"
struct Lerp_Key { char pad[0x18]; Vec3 v; };
struct Lerp_Obj { char pad0[0x1c]; unsigned char flag; char pad1[7]; Lerp_Key* a; Lerp_Key* b; float t; signed char k; };
extern "C" void func_00518490(Vec3* out, Lerp_Key* a, Lerp_Key* b, int k, float t);
extern "C" void func_0053B348(Lerp_Obj* self, Vec3* out) {
  Lerp_Key* a = self->a;
  Lerp_Key* b = self->b;
  if (b != 0) {
    if (self->flag <= 5) {
      float ax = a->v.x;
      float bx = b->v.x;
      float t = self->t;
      out->x = ax + (bx - ax) * t;
      float ay = a->v.y;
      float by = b->v.y;
      out->y = ay + (by - ay) * t;
      float az = a->v.z;
      float bz = b->v.z;
      out->z = az + (bz - az) * t;
      return;
    }
    int k = self->k;
    float t = self->t;
    func_00518490(out, a, b, k, t);
    return;
  }
  if (a == 0) return;
  out->x = a->v.x;
  out->y = a->v.y;
  out->z = a->v.z;
}
