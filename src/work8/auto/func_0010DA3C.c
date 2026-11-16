typedef unsigned int u32;
typedef unsigned char u8;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006F7DB0[];
extern char ro_006F551C[];

void func_0010DA3C(char* a0)
{
  u32* w = (u32*)a0;
  w[0] = (u32)ro_006F7DB0;
  unsigned node = 0x10 + ((int)a0);
  *(u8*)(a0 + 4) = 0;
  w[2] = 0;
  w[5] = node;
  w[3] = (u32)ro_006F551C;
  w[6] = 0;
  w[4] = node;
  w[7] = 0;
  w[9] = w[8] = 0;
}
