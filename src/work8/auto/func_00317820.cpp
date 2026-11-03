/* L2C-CPP */
#define EN_EXTRA
#include "../kb/scripts/out/truework/en210.h"
typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

void func_00317820(unsigned a0)
{
  Eff* e = *(Eff**)((char *)a0 + 0x430);
  if (e != 0 && e->m1c == *(u32*)((char *)a0 + 0x434)) {
    u8 v = 1;
    if (!(e->m3c & 4)) {
      if (!(e->m3c & 0x40)) {
          EffOwner* o = e->m20;
        if (o == 0) return;
        if (e->m24 != o->mc) return;
        if ((s32)o->m4 <= 0) return;
      }
    }
    effFadeImpl(e, v);
  }
}
