#include "albw_types.h"

extern u8* data_0070D858;

void func_00182D24(u8* p) {
  u32 lo = *(u32*)(p + 0x98c);
  u32 hi = *(u32*)(p + 0x990);
  if (hi > lo) {
    *(u32*)(p + 0x98c) = lo + 1;
    return;
  }
  if (*(p + 0x852) != 4) return;
  if (*(data_0070D858 + 0x70) == 4) return;
  void (*fp)(u8*, u32, s32) = *(void (**)(u8*, u32, s32))((char*)*(void**)p + 0xac);
  fp(p, 0, -1);
  u32* f = (u32*)(p + 0x8ac);
  *f = *f & ~0x10u;
}
