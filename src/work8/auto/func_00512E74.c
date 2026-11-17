typedef unsigned int u32;
typedef float f32;
extern u32 func_0014EEB8(char*, void*, u32, f32);
extern void func_00115C54(void*, void*, void*);
u32 func_00512E74(char* p)
{
  f32 z[3];
  f32* d;
  char* o;
  u32 r;
  f32 f;
  f = *(f32*)(*(char**)(p + 0x4cc) + 0x58);
  z[0] = 0.0f;
  z[1] = 0.0f;
  z[2] = 0.0f;
  d = (f32*)(p + 0x524);
  d[0] = 0.0f;
  d[1] = 0.0f;
  d[2] = 0.0f;
  r = func_0014EEB8(p, z, 0xd9f, f);
  o = p + 0x3d0;
  func_00115C54(o, o, p + 0x530);
  return r;
}
