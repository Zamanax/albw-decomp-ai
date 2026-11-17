#include "albw_types.h"
s32 f(u8* s) {
  u8* b = s + 1;
  u8* p = s;
  u32 x;
  while (((u32)p & 3) != 0) {
    u8 c = *p++;
    if (c == 0) return (s32)(p - b);
  }
  for (;;) {
    x = __uqsub8(0x01010101, *(u32*)p);
    p += 4;
    if (x) break;
  }
  s32 r = (s32)(p - b);
  if ((x << 24) != 0) return r - 3;
  if ((x << 16) != 0) return r - 2;
  if ((x << 8) != 0) return r - 1;
  return r;
}
