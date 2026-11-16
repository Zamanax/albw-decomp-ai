#include "albw_types.h"
typedef struct Ptr90 { u8 p[0x18]; f32 f18; u8 q[4]; u32 m20; } Ptr90;
typedef struct A { u8 p[0x90]; Ptr90* m90; } A;
typedef struct G { u8 p[0x80]; f32 f80; } G;
extern G* data_00708998;
extern f32 func_00554D80(void*);
extern f32 func_0055497C(void*);
typedef struct S {
    s8 c0; u8 p1[3]; f32 f4; u8 p2[4];
    union { f32 fc; u32 uc; } cu;
    u8 p3[4]; s32 m14; s32 m18; A* m1c;
} S;

void func_0029F948(S* s, u32 v, s32 flag) {
    if (s->c0 == v) return;
    s->c0 = (s8)v;
    if (v) {
        s->f4 = func_00554D80(s->m1c);
        s->cu.fc = func_0055497C(s->m1c);
    } else {
        A* a = s->m1c;
        Ptr90* q = a->m90;
        s->f4 = q->f18 + data_00708998->f80;
        q = a->m90;
        s->cu.uc = q->m20;
    }
    s->m14 = flag != 0 ? 1 : 10;
    s->m18 = 0;
}
