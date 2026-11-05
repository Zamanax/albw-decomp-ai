#include "albw_types.h"

typedef struct Obj {
  void *m00;
  u8 pad04[0x32];
  u8 m36;
  u8 m37;
  u16 m38;
  u16 m3a;
  u8 pad3c[0x0c];
  u32 m48;
} Obj;

extern u32 data_0070C8E0;
extern u32 ro_00693060;
extern u32 ro_00693064;
extern u32 ro_00693068;
extern u32 ro_00693074;
extern u32 func_005822A0(u32 a, u32 b, u32 c);

u32 func_00547578(Obj *o) {
  u32 r;
  u32 *pd;
  if (o->m48 == 3) return 0;
  pd = &data_0070C8E0;
  r = func_005822A0(*pd, o->m3a, o->m37) != 0;
  if (r) return r;
  if (o->m48 == 7) {
    u32 id = ((u32 *)o->m00)[2];
    if (id == ro_00693060 || id == ro_00693064 || id == ro_00693068 || id == ro_00693074) return 0;
  }
  r = o->m38 != 0 ? func_005822A0(*pd, o->m38, o->m36) : 1;
  return r ^ 1;
}
