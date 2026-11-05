#include "albw_types.h"
extern u32 data_007260E4;
extern u32 data_007260E8;
extern const char ro_006F6314[];
extern void *func_0030DC44(int a, int b);
extern void *func_00556068(void *m);
extern int func_00100174(u32* g);
/* L2C-NOP-SYMBOL __cxa_guard_release */
extern void __cxa_guard_release(u32* g);

void *func_0030DAE0(int a, int b)
{
  void *p;
  u32 *pArg;
  if (func_0030DC44(a, b) == 0) return 0;
  p = func_00556068(func_0030DC44(a, b));
  if (!(data_007260E4 & 1) && func_00100174(&data_007260E4)) {
    u32 *s = &data_007260E8;
    *s = (u32)ro_006F6314;
    __cxa_guard_release(&data_007260E4);
  }
  pArg = &data_007260E8;
  if (p == 0 || ((*(int (**)(void *, void *))(*(int *)p))(p, pArg)) == 0) {
    p = 0;
  }
  return p;
}
