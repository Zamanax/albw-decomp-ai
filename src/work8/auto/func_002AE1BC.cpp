#include "../../work7/gpt17/range.h"
struct Sub {u8 pad[0x7fc];u8 mode;};
struct Obj {u8 pad[0x34];Sub*sub;BitFlag16 flags;};
extern u32 func_002B0D7C(Obj*,s32,f32,s32,s32);
u32 f_002AE1BC(Obj*p){
 u32 r;
 if(p->sub->mode!=2) r=func_002B0D7C(p,10,0.22f,1,0);
 else r=func_002B0D7C(p,10,0.22f,7,0);
 p->flags.set(8);
 return r;
}
