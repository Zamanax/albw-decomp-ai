#include "albw_types.h"
extern u32 data_00726E88;
extern u32 data_00726E8C;
extern const char ro_006DA434[];
extern const char ro_006F626C[];
extern void *func_002D5C70(int a, int b);
extern int func_00100174(u32* g);
/* L2C-NOP-SYMBOL __cxa_guard_release */
extern void __cxa_guard_release(u32* g);

void *func_0028E3D0(int a, int b)
{
  void *p;
  void *r5;
  u32 *pArg;
  p = func_002D5C70(a, b);
  *(u32 *)p = (u32)ro_006DA434;
  {
    void *q = *(void **)((char *)p + 0x28);
    r5 = *(void **)((char *)q + 0x644);
  }
  if (!(data_00726E88 & 1) && func_00100174(&data_00726E88)) {
    u32 *s = &data_00726E8C;
    *s = (u32)ro_006F626C;
    __cxa_guard_release(&data_00726E88);
  }
  pArg = &data_00726E8C;
  if (r5 == 0 || ((*(int (**)(void *, void *))(*(int *)r5))(r5, pArg)) == 0) {
    r5 = 0;
  }
  *(void **)((char *)p + 0x70) = r5;
  *(u8 *)((char *)p + 0x74) = 0;
  *(f32 *)((char *)p + 0x78) = 0.0f;
  *(f32 *)((char *)p + 0x7c) = 0.0f;
  *(f32 *)((char *)p + 0x80) = 0.0f;
  return p;
}
