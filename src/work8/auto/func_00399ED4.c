typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern unsigned func_001151EC(unsigned, unsigned, unsigned);
extern void func_004CEAF0(unsigned);
extern void func_004D8054(float *, unsigned, float);
extern void func_00543104(unsigned);
extern void func_004356B4(unsigned);
void func_00399ED4(unsigned a0)
{
  unsigned lv[3];
  unsigned t1, t2, t3, t5, t6, t7, t8;
  unsigned t9, t10, t11, t14, t15, t16;
  unsigned t17, t18, t19, t20, t24;
  float x1, one;
  t1 = *(unsigned *)((char *)a0 + 0x34);
  t2 = t1 + 0x80;
  t3 = *(unsigned *)((char *)t1 + 0x164);
  *(unsigned *)((char *)t1 + 0x164) = t3 | 0x40000000;
  t5 = *(unsigned *)((char *)a0 + 4);
  t6 = *(unsigned *)((char *)t5 + 0x8D4);
  t7 = *(unsigned *)((char *)t5 + 0x8F8);
  t9 = t7 + (t7 << 1);
  t8 = *(unsigned *)((char *)t6 + 0x24);
  t10 = *(unsigned *)((char *)t8 + 0x14);
  t11 = t10 + (t9 << 4);
  func_001151EC(t2, t11, t2);
  func_004CEAF0(*(unsigned *)((char *)a0 + 0x34));
  t14 = *(unsigned *)((char *)a0 + 4);
  t15 = *(unsigned *)((char *)t14 + 0x8D4);
  t16 = *(unsigned *)((char *)t14 + 0x8EC);
  t17 = *(unsigned *)((char *)t15 + 0x24);
  t18 = t16 + (t16 << 1);
  t19 = *(unsigned *)((char *)t17 + 0x14);
  t20 = t19 + (t18 << 4);
  lv[0] = *(unsigned *)((char *)t20 + 0xC);
  lv[1] = *(unsigned *)((char *)t20 + 0x1C);
  lv[2] = *(unsigned *)((char *)t20 + 0x2C);
  func_004D8054((float *)lv, *(unsigned *)((char *)*(unsigned *)((char *)a0 + 4) + 0x3E8), 0.3f);
  t24 = *(unsigned *)((char *)a0 + 4);
  one = 1.0f;
  x1 = *(float *)((char *)t24 + 0x3D4) + 0.75f;
  *(float *)&lv[1] = x1;
  {
    unsigned *dst = (unsigned *)((char *)a0 + 0x54);
    dst[0] = lv[0];
    dst[1] = lv[1];
    dst[2] = lv[2];
  }
  func_00543104(*(unsigned *)((char *)a0 + 4));
  *(float *)((char *)a0 + 0xA8) = one;
  *(float *)((char *)a0 + 0xAC) = 1.5f;
  *(float *)((char *)a0 + 0xB0) = one;
  func_004356B4(a0 + 0x50);
  return;
}
