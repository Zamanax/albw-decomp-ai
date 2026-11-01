typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006DD8F8[];
extern char ro_006EF760[];
extern char data_00714248[];
extern unsigned func_0010CEE0(unsigned, unsigned, unsigned);
extern unsigned func_0010DA7C(unsigned, unsigned, unsigned);
unsigned func_002DF790(unsigned a0)
{
  unsigned h901, t2, t3, r0;
  if (*(unsigned *)((char *)data_00714248) == 0) {
    t2 = func_0010CEE0(0x18, a0, 4);
    t3 = t2 + 4;
    r0 = t3;
    if (t3 != 0) {
      h901 = a0;
      r0 = func_0010DA7C(t3, h901, 3);
      *(unsigned *)((char *)r0) = (unsigned)ro_006EF760;
    }
    *(unsigned *)((char *)data_00714248 + 4) = r0;
    if (t2 != 0) {
      *(unsigned *)((char *)t2 + 0x14) = 0;
      *(unsigned *)((char *)t2) = (unsigned)ro_006DD8F8;
    }
    *(unsigned *)((char *)data_00714248) = t2;
  }
  return *(unsigned *)((char *)data_00714248);
}
