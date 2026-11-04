typedef unsigned int u32; typedef unsigned short u16;
extern char g_007A06F0[];
extern "C" void func_003DEC28(void*, u32);
struct S { char pad[0x28]; u16 v; };
void target(S* p, float t) {
  if (t < 0.0f) t = 0.0f;
  else if (t > 1.0f) t = 1.0f;
  u16 v = (u16)(t * 32767.0f);
  p->v = v;
  func_003DEC28(g_007A06F0, v);
}
