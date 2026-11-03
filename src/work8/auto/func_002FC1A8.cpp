#include "../../work7/gpt24/range.h"
struct Obj1A4424{char pad[0x59c];Flag32_24 flags;char pad5a0[8];u32 motion;};
extern void func_004FD038(u32*,s32);
extern void func_004FC570(Obj1A4424*);
extern void func_004FCDF4(u32*,s32);
extern "C" void target(Obj1A4424*p){p->flags.set(1);p->flags.set(2);p->flags.set(0x20);p->flags.set(4);func_004FD038(&p->motion,1);func_004FC570(p);p->flags.set(0x80);p->flags.set(2);func_004FCDF4(&p->motion,1);}
