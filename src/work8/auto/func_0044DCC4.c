typedef unsigned int u32;
typedef float f32;
extern void func_00231448(void *);

void func_0044DCC4(char *a0)
{
  char *p;
  f32 v;
  func_00231448(a0 + 0x74);
  p = *(char **)(a0 + 0x11c);
  v = *(f32 *)(p + 0x1c);
  *(f32 *)(a0 + 0xf0) = (-134.0f - v) * 0.05555555555555555f;
  v = *(f32 *)(p + 0x20);
  *(f32 *)(a0 + 0xf4) = v;
  {
    f32 d = v - -41.0f;
    f32 e;
    if (d > 0.0f)
      e = d;
    else
      e = -d;
    *(f32 *)(a0 + 0xf8) = -100.0f - e * 2.0f;
  }
}
