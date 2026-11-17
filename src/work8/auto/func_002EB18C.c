typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char data_00706E20[];
extern char ro_0069391C[];
extern void* func_0052FBA0(void*, u32);
extern u32 func_00588BE4(void*);

float func_002EB18C(char* a0, char* a1)
{
  s32 k;
  if (*(u8*)(a0 + 0xd3d) != 0) return 0.0f;
  k = *(s8*)(a1 + 0x21);
  if (k == 0) {
    void* a = func_0052FBA0((void*)(*(u32*)data_00706E20 + 0x3d800 + 0x3bc), *(u32*)(a1 + 4));
    if (a == 0) return 0.0f;
    if (func_00588BE4(a) != *(u32*)ro_0069391C) return 0.0f;
    return 1.0f;
  }
  if (*(u8*)(a0 + 0xd45) == 1) {
    s32 d = (s32)*(u32*)(a0 + 0xc20) - *(s16*)(a0 + 0x508);
    if (d >= 0x60) return 0.0f;
  } else {
    return 1.0f;
  }
  if (*(u8*)(a0 + 0x8cc) == 0x1f) return 100.0f;
  if (k != 5) return 1.0f;
  {
    u32 t = (*(u32*)(a1 + 0x38) & 0xc000000u) >> 26;
    if (t == 1) return 1.5f;
    if (t == 2) return 1.2f;
  }
  return 1.0f;
}
