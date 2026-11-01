/* L2C-CPP */
typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern unsigned func_00111A64(unsigned);
static inline unsigned bind_0039611C_2_2(unsigned p0, unsigned limit) { return (unsigned)(((unsigned long long)func_00111A64(p0) * limit) >> 32); }

extern unsigned func_0055DC60(unsigned, unsigned);
extern unsigned func_0058A7D4(unsigned);
extern unsigned func_00396AC0(unsigned, unsigned);
unsigned func_00395E88(unsigned a0)
{
  char *t5p; unsigned t1, t5, t8, t12, t16, t17, t20, t24, t27, t31;
  unsigned r;
  t1 = *(unsigned *)((char *)a0);
  t5 = (t1 + 0x800) + 0x3C8;
  t5p = (char *)t5; if (func_0055DC60(t5, *(unsigned char *)(t5p + 0x8C0)) != 0) goto B;
  if (func_0055DC60(t5, *(unsigned char *)(t5p + 0x8C1)) == 0) goto Z;
B:;
  t16 = func_0058A7D4(*(unsigned *)((char *)a0));
  t17 = bind_0039611C_2_2(t16, 101U);
  if ((int)t17 > 0x32) goto Z;
  t20 = *(unsigned *)((char *)a0);
  t24 = (t20 + 0x800) + 0x3C8;
  if (func_0055DC60(t24, *(unsigned char *)((char *)(t20 + 0x1400) + 0x88)) != 0) goto F88;
  t27 = *(unsigned *)((char *)a0);
  t31 = (t27 + 0x800) + 0x3C8;
  if (func_0055DC60(t31, *(unsigned char *)((char *)(t27 + 0x1400) + 0x89)) != 0) goto F89;
  t16 = func_0058A7D4(*(unsigned *)((char *)a0));
  t17 = bind_0039611C_2_2(t16, 101U);
  if ((int)t17 < 0x32) goto F89;
F88:;
  return func_00396AC0(a0, *(unsigned char *)((char *)(*(unsigned *)((char *)a0) + 0x1400) + 0x88));
F89:;
  return func_00396AC0(a0, *(unsigned char *)((char *)(*(unsigned *)((char *)a0) + 0x1400) + 0x89));
Z:;
  t16 = func_0058A7D4(*(unsigned *)((char *)a0));
  r = bind_0039611C_2_2(t16, 101U);
  r = (r <= 10U) ? 2U : 1U;
  *(unsigned char *)((char *)a0 + 0x13) = (unsigned char)r;
  return r;
}
