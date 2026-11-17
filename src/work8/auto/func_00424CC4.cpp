#include "albw_types.h"
#include "vec3.h"
struct CC { u8 p[0x1c]; Vec3 pos; };
struct BB { u8 p[0x10]; CC* c; };
struct AA { BB* b; u8 p[0x70 - 4]; u8 flags; };
struct SS { u8 p0[0x1c]; AA* a; u8 sm[0x34]; f32 m54[9]; u8 m78; };
extern "C" bool func_0068C794(f32* v, f32 t, f32 r, f32 mn, f32 mx);
extern "C" void func_003FFE6C(CC* c, const Vec3& v);
extern "C" void func_0066C0CC(void* m, s32 s);
extern "C" void func_00424CC4(SS* self) {
  Vec3 t; t.setCopy(self->a->b->c->pos);
  bool ch = func_0068C794(&t.x, self->m54[self->m78], 0.5f, 1.0f, 32.0f);
  func_003FFE6C(self->a->b->c, t);
  AA* a = self->a; a->flags |= 2;
  if (ch) func_0066C0CC(self->sm, 2);
}
