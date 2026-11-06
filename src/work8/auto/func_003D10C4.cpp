#include "albw_types.h"
extern void* data_00716788;
extern void* data_00716784;
extern "C" u32 func_003D1810(u32, u32, u32, u32, u32, u32, u32);
extern "C" u32 func_003D135C(u32, u32, u32, u32, u32, u32, u32);
u32 f(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6) {
  if (data_00716788) return func_003D1810(a0, a1, a2, a3, a4, a5, a6);
  if (data_00716784) return func_003D135C(a0, a1, a2, a3, a4, a5, a6);
  return 0xe0810bf8;
}
