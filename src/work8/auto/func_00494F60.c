typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006F6A00[];
extern char ro_006F6A10[];
extern char bss_007A96F0[];
extern char data_00715190[];
extern unsigned func_0010CEE0(unsigned, unsigned, unsigned);
extern unsigned func_0010DA7C(unsigned, unsigned, unsigned);
extern unsigned func_0010CE7C(unsigned);
extern void func_001119F4(unsigned, unsigned);
unsigned func_00494F60(unsigned a0)
{
  unsigned h901, t2, t3, r0, o;
  if (*(unsigned *)((char *)data_00715190) == 0) {
    t2 = func_0010CEE0(0x54, a0, 4);
    t3 = t2 + 0x10;
    r0 = t3;
    if (t3 != 0) {
      h901 = a0;
      r0 = func_0010DA7C(t3, h901, 3);
      *(unsigned *)((char *)r0) = (unsigned)ro_006F6A00;
    }
    *(unsigned *)((char *)data_00715190 + 4) = r0;
    if (t2 != 0) {
      o = func_0010CE7C(t2);
      *(unsigned *)((char *)o) = (unsigned)ro_006F6A10;
      *(unsigned *)((char *)o + 0x20) = 0;
      func_001119F4(o + 0x24, (unsigned)bss_007A96F0);
      r0 = o;
    } else {
      r0 = 0;
    }
    *(unsigned *)((char *)data_00715190) = r0;
  }
  return *(unsigned *)((char *)data_00715190);
}
