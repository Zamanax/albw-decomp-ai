#include "albw_types.h"

struct Src { u32 m0; u32 m4; u32 m8; u32 mC; };
struct Elem { u8 pad[0x30]; Src* m30; u8 rest[0xd0]; };
struct Self { u8 pad[0x620]; f32 fv; u8 pad2[0xc]; u32 cnt; Elem* arr; };
struct Out { u32 m0; u32 m4; u32 m8; u32 mC; u32 m10; u32 m14; };

u32 f(Self* self, Out* o) {
  if (o == 0) return 0;
  int idx = o->m14;
  Elem* e = self->cnt > idx ? &self->arr[idx] : self->arr;
  Src* s = e->m30;
  Out * t3 = o;
  t3->m8 = s->m4;
  u32& dc = t3->mC;
  Src * t6 = s;
  dc = t6->m8;
  f32* fc = (f32*)&dc;
  o->m10 = t6->mC;
  *fc = *fc - self->fv;
  return 4;
}
