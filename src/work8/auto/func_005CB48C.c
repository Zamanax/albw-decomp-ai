typedef unsigned int u32;
typedef unsigned char u8;
extern u32 bss_007A0340[];
extern u32 bss_007A0398[];
extern const char ro_006EFC8C[];
extern void func_00100000(void);
extern void func_00676730(void);
extern void func_003CD930(void);
extern void __aeabi_atexit(void* o, void (*d)(void), void (*h)(void));
extern void func_005902C0(void* a, void (*b)(void), void (*c)(void));

void func_005CB48C(void)
{
  u32 z = 0;
  u32* p = bss_007A0340;
  p[1] = z;
  p[2] = z;
  p[3] = z;
  p[4] = z;
  p[5] = z;
  p[6] = z;
  p[0] = (u32)ro_006EFC8C;
  p[0x15] = z;
  __aeabi_atexit(p, func_00676730, func_00100000);
  u32* q = bss_007A0398;
  q[0] = z;
  q[1] = z;
  q[2] = z;
  q[3] = z;
  *(u8*)&q[4] = (u8)z;
  q[5] = z;
  *(u8*)&q[6] = (u8)z;
  func_005902C0(q, func_003CD930, func_00100000);
}
