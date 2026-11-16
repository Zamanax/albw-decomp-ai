typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern void* data_0070B728;

unsigned func_0053F418(char* a0)
{
  u32 r1 = *(u8*)(a0 + 0x7f);
  if (r1 == 0 || *(u32*)((char*)data_0070B728 + 0x44) != 0) {
    r1 = 0;
  } else {
    r1 = r1 % 18u;
    r1 = ((s32)r1 < 10) ? 1u : 0u;
  }
  return (*(u8*)(a0 + 0x80) == 0) & r1;
}
