typedef unsigned int u32;
typedef int s32;
extern s32 func_003F0080(u32, u32, u32, u32);
extern void func_003EA528(u32);
extern void func_003EDB8C(u32, u32);
extern void func_003F06D8(u32);
extern void func_003F167C(u32);
extern u32 func_003EF244(u32);
extern void (*const data_007161F4[])(u32);

u32 func_003F4D34(u32 a0, u32 a1, u32 a2, u32 a3)
{
  u32 r4;
  s32 r6;
  *(u32 *)((char *)a2 + 0x29C) = 0;
  r4 = *(u32 *)((char *)a2 + 0xDC);
  if (r4 == 0) {
    return a1;
  }
  r6 = func_003F0080(a0 + 4, a1, a2, 0);
  if (a3 == 0) {
    while (r4 != 0) {
      u32 nx;
      if (*(s32 *)r4 >= *(s32 *)(r4 + 4)) {
        nx = *(u32 *)(r4 + 0x140);
        func_003EA528(r4);
        r4 = nx;
      } else {
        if (r6 >= 0) {
          func_003F06D8(r4);
          data_007161F4[r6](r4);
        } else {
          func_003EDB8C(a2, r4);
        }
        *(u32 *)((char *)a2 + 0x29C) += 1;
        r4 = *(u32 *)(r4 + 0x140);
      }
    }
  } else {
    goto check;
    do {
      func_003F167C(r4);
      data_007161F4[r6](r4);
      *(u32 *)((char *)a2 + 0x29C) += 1;
      r4 = *(u32 *)(r4 + 0x140);
      if (r4 == 0) {
        break;
      }
    check:
      ;
    } while (r6 >= 0);
  }
  return func_003EF244(a0 + 4);
}
