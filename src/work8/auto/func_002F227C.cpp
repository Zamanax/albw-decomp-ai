#include "flags.h"
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct Obj {
    char p0[0x59c];
    Flag32 m59c;
    char p1[0xb0c - 0x5a0];
    u32 mB0C;
    u32 mB10;
    f32 mB14;
    char p2[0xb98 - 0xb18];
    f32 mB98;
} Obj;

typedef struct Tail {
    u32 m0;
    u32 m4;
    f32 m8;
} Tail;

extern s32 func_0058AB74(Obj*);
extern void func_004FABDC(Obj*, u32, s32, s32);

void func_002F227C(Obj* o) {
    o->m59c.set(4);
    o->m59c.set(0x80);
    o->m59c.set(1);
    o->m59c.set(2);
    Tail* t = (Tail*)&o->mB0C;
    t->m4 = 0x1e;
    t->m8 = 0.0333333343f;
    t->m0 = 0;
    s32 r = func_0058AB74(o);
    if (r != 0x1e && r != 0x1c && r != 0x1d) {
        func_004FABDC(o, 0x18, -1, 0);
    }
    o->mB98 = 0.0f;
}
