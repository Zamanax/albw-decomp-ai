typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006F5988[];
extern char ro_00694F80[];
extern char data_00709DF8[];
extern char data_0070C8E0[];
extern unsigned func_00582260(unsigned, signed char, unsigned);
extern unsigned func_00691884(unsigned, unsigned *, unsigned, unsigned);

unsigned func_004B3B10(void)
{
  unsigned lv[2];
  char *ev = *(char **)data_00709DF8;
  unsigned p;
  unsigned s, n;
  p = func_00582260(*(unsigned *)data_0070C8E0, *(signed char *)(ev + 0x18), *(unsigned *)(ev + 0x1c));
  p = p + 4;
  s = (unsigned)ro_00694F80;
  n = (unsigned)ro_006F5988;
  lv[0] = n;
  lv[1] = s;
  return func_00691884(p, lv, s, n) != 0 ? 1 : 0;
}
