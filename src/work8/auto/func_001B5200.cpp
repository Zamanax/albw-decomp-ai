typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned char u8;
extern void func_004FC07C(void*, s32, s32, u32);
struct Sub800 { u8 pad0[0x108]; f32 m908; u32 m90c; u8 pad110[0x150 - 0x110]; f32 v150; };
struct Obj1B5200 {
  u8 pad0[0x3dc];
  f32 v3dc;
  f32 v3e0;
  f32 v3e4;
  u8 pad3e8[0x800 - 0x3e8];
  Sub800 s800;
  u8 pad954[0x988 - 0x954];
  f32 m988;
};
void f1B5200(Obj1B5200* p) {
  p->s800.m908 = p->m988;
  p->s800.m90c = 2;
  p->v3dc = 0.0f;
  p->v3e0 = 0.0f;
  p->v3e4 = 0.0f;
  p->s800.v150 = 0.0f;
  func_004FC07C(p, 4, -1, 0);
}
