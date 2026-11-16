typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

extern f32* data_007162C0;

typedef struct Sub { u8 pad0[0x4e]; u16 f4e; u8 pad1[8]; u16 f58; } Sub;
typedef struct P { u8 pad0[0x500]; Sub sub; } P;
typedef struct A { u8 pad0[0xd8]; P* p; } A;
typedef struct B { s32 v0; u8 pad0[0xa4]; f32 fa8; f32 fac; u8 pad1[0xa0]; s32 f150; } B;
typedef struct Ent { f32 a; f32 b; u32 c; } Ent;

void func_003EAA08(A* self, B* b)
{
    P* p = self->p;
    Sub* q = &p->sub;
    Ent* e = (Ent*)(q->f58 + (u8*)p);
    Ent * t1 = e;
    int idx = (s32)(((f32)b->v0) * t1->b);
    f32 v = data_007162C0[(b->f150 * t1->c + idx) & 0x7f];
    Sub * t0 = q;
    f32 r = 1.0f - v * t1->a;
    if (t0->f4e & 2) b->fa8 = r;
    if (t0->f4e & 4) b->fac = r;
}
