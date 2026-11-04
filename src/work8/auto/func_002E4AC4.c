typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern void* data_0070FB60;
extern unsigned func_0055696C(unsigned, unsigned);
extern signed int func_0058A468(unsigned);

float func_002E4AC4(unsigned a0, unsigned a1)
{
  signed int t1;
  unsigned r;
  float s0;
  t1 = *(signed char *)((char *)a1 + 0x21);
  if (t1 == 0xd) {
    r = func_0055696C((unsigned)data_0070FB60, 0xc);
    if (r >= 3) {
      return 100.0f;
    }
    return (float)func_0058A468(a0) / ((float)*(unsigned short *)((char *)a1 + 0x30) * 3.0f);
  }
  if (t1 == 2 || *(unsigned char *)((char *)a1 + 0x23) == 3) {
    s0 = 0.0f;
  } else {
    s0 = 1.0f;
  }
  return s0;
}
