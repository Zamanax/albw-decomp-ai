#include "../../work6/gpt13/spawn.h"
extern const s32 ro_00693918;
extern const s32 ro_006930F0;
extern const s32 ro_006930F4;
void func_004E0490(const Vec3&pos,const u32&b,u16 x,u16 y,s32 flag){SpawnParam p;p.m0=func_0019B04C(flag==0?ro_006930F0:ro_006930F4);p.m50=data_0070C8E0->func_00581D60();p.m4c=b;copyPos(p.m4,pos);p.m28=0;p.m2a=x;p.m2c=y;p.m20=0;func_004C43E0(data_00706E20,p);}
