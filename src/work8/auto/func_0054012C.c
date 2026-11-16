typedef unsigned int u32;
typedef float f32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523

u32 func_0054012C(char* a0)
{
  char* q = *(char**)(a0 + 0x10);
  char* p;
  f32 s0;
  f32 s1;
  f32 t;
  if (*(u32*)(q + 0x5b0) != 0x3f800000) {
    return 0;
  }
  if (*(unsigned short*)(a0 + 0x42) != 0x46) {
    return 1;
  }
  p = *(char**)(a0 + 0x48);
  s1 = *(f32*)(p + 0x80);
  s0 = *(f32*)(p + 0x78);
  if (s0 > s1) {
    return 1;
  }
  t = *(f32*)(*(char**)(p + 0x30) + 4) + 1.0f;
  if (t < s0) {
    return 1;
  }
  if (*(u32*)(a0 + 0x44) >= 2) {
    return 0;
  }
  return 1;
}
