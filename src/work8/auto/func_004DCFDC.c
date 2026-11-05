typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

static unsigned arrAt_C_14(unsigned a, int i) { return (unsigned)i < *(unsigned *)(a + 0xC) ? *(unsigned *)(a + 0x14) + i * 4 : *(unsigned *)(a + 0x14); }

void func_004DCFDC(unsigned a0)
{
  unsigned t2, t4;
  void (*fp)(unsigned, unsigned, int);
  *(unsigned short *)((char *)a0 + 0x9ba) = 0;
  *(float *)((char *)a0 + 0x834) = 0.2f;
  fp = *(void (**)(unsigned, unsigned, int))((char *)(*(unsigned *)a0) + 0xac);
  fp(a0, 5, -1);
  t2 = *(unsigned *)((char *)a0 + 0x7ac);
  t4 = arrAt_C_14(t2, 0);
  *(float *)((char *)t4 + 0x10) = 2.0f;
  return;
}
