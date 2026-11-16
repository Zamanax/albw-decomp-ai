typedef unsigned int u32;
typedef int s32;
extern u32 func_00520FD4(void*);
extern u32 func_0058E2B8(s32*);

s32 func_004C0CC4(char* p)
{
  s32 r = 0;
  if (func_00520FD4(p) == 0) {
    if ((*(u32*)(p + 0x8ac) & 0x1000) == 0) {
      s32 sum = *(s32*)(p + 0x824) + *(s32*)(p + 0x820) + *(s32*)(p + 0x3e8);
      u32 q = func_0058E2B8(&sum);
      float v = 1.0f - (float)q * 9.313225746154785e-10f;
      if (v > 1.0f) v = 1.0f; else if (v < 0.0f) v = 0.0f;
      r = (s32)((v * v) * (float)*(s32*)(p + 0x8cc));
    }
  }
  return r;
}
