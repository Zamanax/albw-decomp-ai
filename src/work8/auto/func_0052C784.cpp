typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

#include "vec3.h"

struct Sub800 { u8 pad[0x38]; f32 m38; };
struct Obj { u8 pad[0x3d0]; f32 m3d0; f32 m3d4; f32 m3d8; u8 pad2[0x800 - 0x3dc]; Sub800 m800; };
struct Player70FB60 { char pad[0x24]; u32* m24; };
extern Player70FB60* data_0070FB60;
extern Vec3* func_00520FC0(Obj*);
extern void func_004D8054(Vec3* v, u32 angleIdx, f32 d);
extern void func_00583B90(Obj*, void*);
void func_0052C784(Obj* self, Vec3* out) {
  if (out) {
    Player70FB60* pl = data_0070FB60;
    if (pl) {
      Vec3* p = func_00520FC0(self);
      f32 dx = self->m3d0 - p->x;
      f32 dz = self->m3d8 - p->z;
      f32 d2 = dx * dx + dz * dz;
      if (d2 < 0.8f * 0.8f) {
        *out = *p;
        func_004D8054(out, *pl->m24, 1.0f);
        out->y = self->m3d4 + self->m800.m38;
        return;
      }
    }
  }
  func_00583B90(self, out);
}
