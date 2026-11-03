typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_00693950[];
extern unsigned func_00588BE4(unsigned);
extern unsigned func_001AB87C(unsigned);
extern void func_004F8638(unsigned, int);
void func_001ABB68(unsigned a0)
{
  unsigned h901, t1, t3, t4;
  t1 = func_00588BE4(a0);
  h901 = *(unsigned *)((char *)ro_00693950);
  if (t1 == h901) {
    func_001AB87C(a0);
    t3 = a0 + 0x800;
    *(float *)((char *)t3 + 0x1B8) = 1.0f;
    t4 = *(unsigned *)((char *)a0 + 0x40C);

    if (t4 != 0) {
      *(unsigned *)((char *)t4 + 0x158) = *(unsigned *)((char *)t3 + 0x1B8);
    }
  }
  func_004F8638(a0, -1);
}
