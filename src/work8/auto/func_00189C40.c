typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_00693884[];
extern char ro_00693888[];
extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern unsigned func_00588BE4(unsigned);
extern unsigned func_00187F18(unsigned, unsigned);
extern unsigned func_00659544(unsigned, unsigned);
unsigned func_00189C40(unsigned a0, unsigned a1)
{
  unsigned t, u, w;
  signed char k;
  if (*(unsigned char *)((char *)a0 + 0x500) == 7) goto L_ret0;
  if (func_00187F18(a0, a1) != 0) goto L_ret1;
  k = *(signed char *)((char *)a0 + 0x500);
  if (k == 2) goto L_ce8;
  if (k == 6) goto L_ret1;
  t = func_0052FBA0((*(unsigned *)((char *)data_00706E20) + 0x3D800) + 0x3BC, *(unsigned *)((char *)a1 + 0x28));
  if (t == 0) goto L_ret0;
  u = func_00588BE4(t);
  w = *(unsigned *)((char *)ro_00693884);
  if (u != w) {
    if (func_00588BE4(t) != *(unsigned *)((char *)ro_00693888)) goto L_ret0;
  }
  func_00659544(a0 + 0x4FC, 6);
  return 1;
L_ce8:
  u = *(unsigned *)((char *)a1 + 0x34);
  if (u == 0) goto L_ret0;
  if ((*(unsigned short *)((char *)u + 4) & 0xFF) != 2) goto L_ret0;
  if ((*(unsigned short *)((char *)a1 + 0x20) & 0x1F) == 7) goto L_ret1;
  func_00659544(a0 + 0x4FC, 6);
L_ret1:
  return 1;
L_ret0:
  return 0;
}
