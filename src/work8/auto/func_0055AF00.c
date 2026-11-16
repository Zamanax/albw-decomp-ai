typedef unsigned char u8;
typedef unsigned int u32;
extern const u8 ro_006A003B[];
extern const u8 ro_006A0034[];
extern const u8 ro_006A0037[];
extern const u8 ro_006A0045[];
extern u32 func_00426294(u8);

u32 func_0055AF00(u8* p)
{
  u8 idx = p[0x2c];
  switch (p[0x2d]) {
  case 0:
    return func_00426294(ro_006A003B[idx]);
  case 1:
    if (p[0x2f] == 0)
      return func_00426294(ro_006A0037[idx]);
    return func_00426294(ro_006A0034[idx]);
  case 2:
    return func_00426294(ro_006A0045[idx]);
  default:
    return func_00426294(ro_006A003B[idx]);
  }
}
