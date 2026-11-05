typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef float f32;
struct Control {u32 opaque;};

#include "flags.h"

struct Obj {
 u8 pad0[0x3dc];
 f32 f3dc;
 f32 f3e0;
 f32 f3e4;
 u8 pad1[0x59c-0x3e8];
 BitFlag32 flags;
 u8 pad2[8];
 Control ctl;
};
void func_004FCDF4(Control* c, bool b);
void func_004FD038(Control* c, bool b);
void func_004FC07C(Obj* e, s32 a, s32 b, s32 c);

void f_001AC370(Obj* p) {
 p->flags.set(2);
 func_004FCDF4(&p->ctl, true);
 p->flags.set(0x80);
 p->flags.set(4);
 func_004FD038(&p->ctl, true);
 p->f3dc = 0.0f;
 p->f3e0 = 0.0f;
 p->f3e4 = 0.0f;
 func_004FC07C(p, 0, -1, 0);
}
