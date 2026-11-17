typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern "C" float sqrtf(float);
struct V3 { f32 x, y, z; };
struct T27A0 { u8 pad0[0x44]; V3* p44; u8 pad1[0x324 - 0x48]; u8 b324; u8 pad2[0x4cc - 0x325]; f32 f4cc; };
u32 f(T27A0* self, f32 d) {
  u8 b = self->b324;
  if (!(b & 1)) {
    if (!(b & 8)) return 0;
  }
  if (0.0f > d) return 1;
  f32 e = self->f4cc;
  if (e == 0.0f) return 0;
  V3* v = self->p44;
  f32 x = v->x;
  f32 y = v->y;
  f32 z = v->z;
  f32 sq = x * x;
  sq = sq + y * y;
  sq = sq + z * z;
  f32 len = sqrtf(sq);
  s32 bits = *(s32*)&len;
  if (bits > 0x3d449ba6) return 1;
  return 0;
}
