typedef unsigned int u32;
typedef unsigned char u8;

void func_001A7650(unsigned a0)
{
  u32 t1;
  u8 *p = *(u8 **)(a0 + 0x8e4);
  p[0x61] = 0;
  a0 = a0 + 0x968;
  t1 = *(u32 *)a0;
  if ((t1 != 0) && (*(u32 *)(t1 + 0x1C) == *(u32 *)(a0 + 4))) {
    u32 t0 = *(u32 *)(t1 + 0x20);
    u8 v = 1;
    if (t0 != 0 && *(u32 *)(t1 + 0x24) == *(u32 *)(t0 + 0xC) && (int)*(u32 *)(t0 + 4) > 0) {
      *(u8 *)(t0 + 0x280) = v;
    }
    *(u32 *)(t1 + 0x3C) = (*(u32 *)(t1 + 0x3C) & ~4u) | 8u;
  }
  return;
}
