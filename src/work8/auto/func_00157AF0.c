typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

extern void func_004FABDC(void*, u32, u32, u32);

typedef struct { u8 pad[0x22]; u8 b22; } Inner420;
typedef struct {
  u8 pad0[0x3dc];
  f32 f3dc, f3e0, f3e4;
  u32 m3e8;
  u8 pad1[0x420 - 0x3ec];
  Inner420* p420;
  u8 pad2[0xa34 - 0x424];
  u32 ma34;
} Obj;

void func_00157AF0(Obj* self) {
  Inner420* in = self->p420;
  in->b22 = 1;
  f32 z = 0.0f;
  self->f3dc = z;
  self->f3e4 = z;
  u32 v = self->m3e8;
  if (v < 0x80000000u) {
    func_004FABDC(self, 7, 0, 0);
  } else {
    func_004FABDC(self, 4, 0, 0);
  }
  self->ma34 = 0;
}
