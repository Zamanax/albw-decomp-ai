#include "../../work7/gpt24/range.h"
struct Obj1A4424{char pad[0x3dc];f32 f3dc;f32 f3e0;f32 f3e4;char pad3e8[0x4f8-0x3e8];f32 f4f8;char pad4fc[0x59c-0x4fc];Flag32_24 flags;char pad5a0[8];u32 motion;};
extern void func_004FCD5C(u32*,s32);
extern void func_004FD038(u32*,s32);
extern void func_004FB024(Obj1A4424*);
extern "C" void target(Obj1A4424*p){p->f3dc=0;p->f3e0=0;p->f3e4=0;p->flags.clear(1);func_004FCD5C(&p->motion,0);p->flags.clear(4);func_004FD038(&p->motion,0);p->f4f8=0.5f;func_004FB024(p);}
