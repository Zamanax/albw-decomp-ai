/* L2C-CPP */
typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern unsigned func_00111A64(unsigned);
static inline unsigned bind_003B7680_0_2(unsigned p0, unsigned limit) { return (unsigned)(((unsigned long long)func_00111A64(p0) * limit) >> 32); }
extern unsigned func_00111A64(unsigned);
static inline unsigned bind_003B7680_0_7(unsigned p0, unsigned limit) { return (unsigned)(((unsigned long long)func_00111A64(p0) * limit) >> 32); }

extern unsigned func_0058A7D4(unsigned);
extern unsigned func_002B7634(unsigned, unsigned);
void func_003B0EF8(unsigned a0)
{
  unsigned t2, t3, t10, t11, t14;
  ((unsigned (*)(unsigned))*(unsigned *)((char *)*(unsigned *)((char *)a0) + 0x130))(a0);
  ((unsigned (*)(unsigned))*(unsigned *)((char *)*(unsigned *)((char *)a0) + 0x100))(a0);
  t2 = func_0058A7D4(*(unsigned *)((char *)a0 + 0x48));
  t3 = (unsigned)bind_003B7680_0_2(t2, 31U);
  *(unsigned *)((char *)a0 + 0x4C) = t3 + 0x1E;
  t10 = func_0058A7D4(*(unsigned *)((char *)a0 + 0x48));
  t11 = (unsigned)bind_003B7680_0_7(t10, 101U);
  if ((int)t11 <= 0x32) {
    *(unsigned char *)((char *)*(unsigned *)((char *)a0 + 0x48) + 0x935) = 2;
    return;
  }
  t14 = *(unsigned *)((char *)a0 + 0x48);
  *(unsigned char *)((char *)t14 + 0x935) = 3;
  func_002B7634(t14, 3);
  return;
}
