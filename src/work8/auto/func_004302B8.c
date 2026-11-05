typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

void func_004302B8(unsigned a0)
{
  unsigned t1;
  u32 *q;
  float x3, x4, x5;
  t1 = *(unsigned *)((char *)a0 + 0x58);
  q = (u32 *)((char *)t1 + 0xD0);
  {
    u32 *d = (u32 *)((char *)a0 + 0x34);
    d[0] = q[0];
    d[1] = q[1];
    d[2] = q[2];
    d[3] = q[3];
    d[4] = q[4];
  }
  {
    float *s48 = (float *)((char *)a0 + 0x48);
    *s48 = *(float *)(q + 5);
    {
      float *v = (float *)((char *)a0 + 4);
      x3 = v[0];
      x4 = v[1];
      x5 = v[2];
    }
    *(float *)((char *)a0 + 0x34) = (*(float *)((char *)a0 + 0x34)) + x3;
    *(float *)((char *)a0 + 0x38) = (*(float *)((char *)a0 + 0x38)) + x4;
    *(float *)((char *)a0 + 0x3C) = (*(float *)((char *)a0 + 0x3C)) + x5;
    *(float *)((char *)a0 + 0x40) = (*(float *)((char *)a0 + 0x40)) + x3;
    *(float *)((char *)a0 + 0x44) = (*(float *)((char *)a0 + 0x44)) + x4;
    *(float *)((char *)a0 + 0x48) = *s48 + x5;
  }
}
