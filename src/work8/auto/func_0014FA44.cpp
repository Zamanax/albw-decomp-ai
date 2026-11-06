typedef unsigned int u32; typedef int s32; typedef unsigned short u16; typedef short s16; typedef unsigned char u8; typedef signed char s8; typedef float f32;
struct Vec3 {f32 x,y,z;};
struct Blk {f32 w0,w1,w2,w3,w4,w5;};
union Raw {Blk f; u32 u[6];};
struct Init {u32 m0; Blk m;};
struct Desc {Vec3* m0; Raw m4; u32 m1c; u8 m20;};
struct Obj {char p0[0x54]; u16 m54; char p56[0x2cc-0x56]; u32 m2cc; char p2d0[0x3a0-0x2d0]; u32 m3a0;};
extern void* data_00709D28;
Init* func_004331A0(Init*);
void func_004A8F40(void*, Desc*, u32);
void func_0014FA44(Obj* p, Vec3* out, u32 a2, u32 a3, u32 sb, u32 a6, u32 a7) {
  Init tmp;
  Init* q = func_004331A0(&tmp);
  Desc d;
  d.m4.f = q->m;
  d.m1c = 0;
  d.m20 = 0;
  d.m4.u[2] = p->m2cc;
  d.m4.u[0] = a3;
  d.m4.u[1] = a6;
  d.m0 = out;
  d.m1c = a2;
  *(u16*)&d.m4.u[3] = p->m54;
  u32 z = a7;
  if (z == 0) z = p->m3a0;
  d.m4.u[5] = z;
  func_004A8F40(data_00709D28, &d, sb);
}
