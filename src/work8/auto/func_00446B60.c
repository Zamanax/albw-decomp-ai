typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char data_007142C8[];
extern unsigned func_0058DC54(unsigned);
extern void func_0051AF38(unsigned);
extern void func_0066CC58(unsigned, unsigned);
extern unsigned func_0058DABC(unsigned);
extern unsigned func_0058DE90(unsigned);
extern unsigned func_0058D6D0(unsigned);
extern unsigned func_0058D808(unsigned);
extern void func_00519D74(unsigned);
extern unsigned func_0051B0B4(unsigned);

void func_00446B60(unsigned a0)
{
  char *s = (char *)a0 + 0x200;
  unsigned char f = *(unsigned char *)((char *)a0 + 0x284);
  unsigned t0 = *(unsigned *)((char *)((unsigned)data_007142C8));
  unsigned t2, t4, t7, t9, t12;
  if (f != 0) {
    t2 = func_0058DC54(t0);
    if (t2 != 0) func_0051AF38(*(unsigned *)((char *)((unsigned)data_007142C8)));
    func_0066CC58(a0 + 0x158, 9);
    return;
  }
  t2 = func_0058DABC(t0);
  if (t2 != 0) {
    t4 = func_0058DE90(*(unsigned *)((char *)((unsigned)data_007142C8)));
    if (t4 != 0 || *(unsigned char *)(s + 0x93) != 0) {
      t7 = func_0058D6D0(*(unsigned *)((char *)((unsigned)data_007142C8)));
      if (t7 != 0) {
        t9 = func_0058D808(*(unsigned *)((char *)((unsigned)data_007142C8)));
        if (t9 != 0) func_00519D74(*(unsigned *)((char *)((unsigned)data_007142C8)));
      }
    }
  }
  t12 = *(unsigned *)((char *)a0 + 0x210);
  if (*(unsigned char *)((char *)t12 + 0x5F) == 0 && *(unsigned char *)((char *)t12 + 0x5D) != 0) return;
  if (func_0058DE90(*(unsigned *)((char *)((unsigned)data_007142C8))) == 0) return;
  if (func_0051B0B4(*(unsigned *)((char *)((unsigned)data_007142C8))) == 0) return;
  func_0066CC58(a0 + 0x158, 7);
}
