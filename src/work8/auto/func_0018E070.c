typedef unsigned int u32;
typedef unsigned char u8;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_0069315C[];
extern char ro_00693114[];
extern char ro_00693264[];
extern char ro_00693268[];
extern char ro_0069326C[];
extern char data_00706E20[];
extern unsigned func_0052FBA0(unsigned, unsigned);
extern unsigned func_00588BE4(unsigned);
unsigned func_0018E070(unsigned a0, unsigned a1)
{
  unsigned c, t8, t9, h901, h902, h903, h904, h905;
  char *p;
  p = (char *)a0 + 0x400;
  c = 0;
  if (*(u8 *)((char *)a0 + 0x4a0) == 0) c = 1;
  if (*(u8 *)(p + 0xa1) != 0) goto La;
  if ((int)*(u32 *)((char *)a0 + 0x49c) <= 1) goto Lb;
La:
  if (c == 0) goto Lz;
Lb:
  t8 = func_0052FBA0((*(u32 *)((char *)data_00706E20) + 0x3D800) + 0x3BC, *(u32 *)((char *)a1 + 0x28));
  if (t8 == 0) goto Lz;
  t9 = func_00588BE4(t8);
  h901 = *(u32 *)((char *)ro_0069315C);
  if (t9 == h901) goto Lo;
  h902 = *(u32 *)((char *)ro_00693114);
  if (t9 == h902) goto Lo;
  h903 = *(u32 *)((char *)ro_00693264);
  if (t9 == h903) goto Lo;
  h904 = *(u32 *)((char *)ro_00693268);
  if (t9 == h904) goto Lo;
  h905 = *(u32 *)((char *)ro_0069326C);
  if (t9 != h905) goto Lz;
Lo:
  return 1;
Lz:
  return 0;
}
