typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;

extern u32 func_004F9434(u32);
extern void func_004F9FC4(u32, u32);
extern void func_004FA124(u32, s32, s32);
extern void func_004FBA3C(u32, s32, s32);
extern u32 func_002AB1CC(u8, s32, s32);

u32 func_001A3374(u32 a0, u32 a1, u32 a2)
{
  u32 r6 = a1;
  u32 v;
  if (*(u8 *)(a0 + 0x4B5) == 0) v = *(u32 *)(a0 + 0x430);
  else v = *(u32 *)(a0 + 0x434);
  if (func_004F9434(v) == 5) {
    if (*(u8 *)(a2 + 0x24) != 5) {
      func_004F9FC4(a0, *(u32 *)(a0 + 0x43C));
      func_004FA124(a0, *(s8 *)(a2 + 0x24), 0);
      func_004FBA3C(a0, *(s8 *)(a2 + 0x24), *(s8 *)(a2 + 0x25));
    }
    return 0;
  }
  if (*(s16 *)(a0 + 0x508) > 0) {
    u32 t = a1 & 0xFF;
    if (t == 30 || t - 14 <= 3) {
      u32 x = *(u32 *)(a0 + 0x984);
      u32 y = *(u32 *)(a0 + 0x988);
      if (x < y) *(u32 *)(a0 + 0x984) = x + 1;
      if (x >= y) return 0;
      r6 = func_002AB1CC((u8)a1, (s32)-1, 0);
    }
  }
  *(u32 *)(a0 + 0x5A0) |= 0x80;
  return r6;
}
