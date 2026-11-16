typedef unsigned int u32;
extern u32 func_00588BE4(void*);
extern const u32 ro_006930E0;
extern const u32 ro_006936A4;
extern const u32 ro_00693800;
extern const u32 ro_00693804;
extern const u32 ro_00693808;
extern u32 data_0070D61C[];

u32 func_0030B134(void* a0, u32 a1)
{
  if (a1 == 0) {
    u32 (*fp)(void*) = *(u32 (**)(void*))((char*)*(void**)a0 + 0x44);
    return func_00588BE4((void*)fp(a0));
  }
  if (a1 == 0x64) return ro_006930E0;
  if (a1 == 0x65) return ro_006936A4;
  if (a1 == 0xC8) return ro_00693800;
  if (a1 == 0xC9) return ro_00693804;
  if (a1 == 0xCA) return ro_00693808;
  if (a1 - 1 < 0x4f) return data_0070D61C[a1];
  return 0xffff;
}
