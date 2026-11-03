#include "../import_mmaupas/include/albw_types.h"
struct Obj4F2E24 { u8 pad0[0x3dc]; f32 vx,vy,vz; u8 pad3e8[0x914-0x3e8]; f32 m914; };
extern bool func_004FABDC(void*,u16,s32,bool);
extern void func_004F3158(void*);
void func_004F2E24(Obj4F2E24*p){for(int i=0;i<3;++i)(&p->vx)[i]=0.0f;p->m914=0.0f;func_004FABDC(p,1,-1,false);func_004F3158(p);}
