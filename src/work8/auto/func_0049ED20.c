typedef unsigned char u8;
typedef int s32;

void func_0049ED20(u8* dst, const u8* a, const u8* b, float t)
{
  float c, fa, fd, lo, hi;
  lo = 0.0f;
  hi = 1.0f;
  s32 ia, ib;
  c = t;
  if (c < lo) c = lo;
  else if (c > hi) c = hi;
  ia = a[0];
  ib = b[0];
  fa = (float)ia;
  fd = (float)(ib - ia);
  dst[0] = (u8)(s32)(fa + fd * c);
  ia = a[3];
  ib = b[3];
  fa = (float)ia;
  fd = (float)(ib - ia);
  dst[3] = (u8)(s32)(fa + fd * c);
  ia = a[2];
  ib = b[2];
  fa = (float)ia;
  fd = (float)(ib - ia);
  dst[2] = (u8)(s32)(fa + fd * c);
  ia = a[1];
  ib = b[1];
  fa = (float)ia;
  fd = (float)(ib - ia);
  dst[1] = (u8)(s32)(fa + fd * c);
}
