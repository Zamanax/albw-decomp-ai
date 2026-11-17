typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
extern s8 data_00716118;
extern void func_00102550(u32, u8, u32);
extern void func_0010C1B8(void);
void func_0010A98C(u32 a0)
{
  u8 *base = (u8 *)0x1FF80000u;
  int r = (int)(a0 >> 27);
  u32 f;
  if (a0 & 0x80000000u) r -= 0x20;
  f = (base[0x14] & 1) | (u32)(int)data_00716118;
  if (f == 0) {
    if (r == -1) func_00102550(a0, 0, (u32)__return_address());
    func_0010C1B8();
  } else if (r != -7 && r != 1) {
    func_00102550(a0, 0, (u32)__return_address());
  }
}
