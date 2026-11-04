typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern unsigned func_005811E8(unsigned);
extern unsigned func_00110848(unsigned, unsigned, unsigned);
extern unsigned func_004A1B9C(unsigned, unsigned, unsigned);
extern unsigned func_0066B43C(unsigned, unsigned);
void func_00507CD8(unsigned a0)
{
  unsigned lv[2];
  unsigned k1, t4, t5, t6, t9;
  u32 *s;
  if (func_005811E8(a0 + 0x508) == 0) {
    if (func_005811E8(a0 + 0x500) == 0) {
      s = (u32 *)((char *)a0 + 0x500);
      k1 = (unsigned)"Launch";
      if (*(unsigned *)((char *)a0 + 0x344) != 0) {
        t4 = s[0];
        if (t4 != 0) {
          t5 = *(unsigned *)((char *)t4 + 0x1C);
          t6 = s[1];
          if (t5 == t6) {
            func_00110848(t4, t6, t5);
          }
        }
        func_004A1B9C((unsigned)&lv[0], *(unsigned *)((char *)a0 + 0x344), k1);
        t9 = *(unsigned *)((char *)&lv[1]);
        s[0] = lv[0];
        s[1] = t9;
      } else {
        s[0] = 0;
        s[1] = 0;
      }
    }
  }
  if (*(unsigned short *)((char *)a0 + 0x2C) == 1) {
    if (*(int *)((char *)a0 + 0x510) > 0xB4) {
      func_0066B43C(a0 + 0x510, 2);
    }
  } else {
    if (*(int *)((char *)a0 + 0x510) > 0x1E) {
      func_0066B43C(a0 + 0x510, 2);
    }
  }
}
