typedef unsigned char u8;
typedef int s32;
typedef float f32;
struct Child165F { u8 pad[0x1a4]; s32 value; };
struct Global165F { u8 pad[0x18]; Child165F* child; };
extern Global165F* data_00708998;
struct Obj20 { u8 pad[0x20]; f32 f20; };
void func_004CD45C(Obj20* self) {
  Global165F* g = data_00708998;
  if (g && g->child) {
    s32 v = g->child->value;
    v = v > 0x38e38e38 ? 0x38e38e38 : v;
    v = v < 0x1c71c71c ? 0x1c71c71c : v;
    self->f20 = (f32)(v + (s32)0xe38e38e4) * 2.0954757928848267e-9f;
  } else {
    self->f20 = 1.0f;
  }
}
