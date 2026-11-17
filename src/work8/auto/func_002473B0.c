typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern void func_0014E2A0(void*, u32, void*, u32, u32, u32);
extern void func_0065F560(void*, u32);
void func_002473B0(char* p)
{
  f32 f, r;
  u32 z = 0;
  char* q = p + 0x400;
  char* s = p;
  func_0014E2A0(p, *(u32*)(p + 0x444), q + 0x94, 0x1000, z, z);
  f = (f32)*(s32*)(s + 0x410);
  r = *(f32*)(s + 0x464) + (*(f32*)(s + 0x45c) * (f * f) + *(f32*)(s + 0x460) * f);
  *(f32*)(s + 0x454) = r;
  if (*(s32*)&f >= 0x41a00000)
    func_0065F560(s + 0x410, 2);
}
