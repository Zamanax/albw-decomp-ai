#include "vec3.h"

typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef float f32;

struct Elem44 { f32 f[7]; Vec3 v; s16 m28; s16 pad2a; };
extern "C" Elem44 data_00708AA0[];

struct ActorP { char pad[0x3d0]; Vec3 pos; };

struct Ctl0C {
    virtual void f0(void* a, Vec3* b);
};

struct S2FCBG { char pad[0x18]; void* m18; };
extern "C" S2FCBG* data_00708998;
extern "C" void func_001E8268(void*, void*, void*, void*);

struct Obj36C0 {
    char pad4[4];
    ActorP* m4;
    char pad8[4];
    Ctl0C* mC;
    char pad10[0xc];
    u32 m1c;
    char pad20[8];
    Vec3* m28;
    Ctl0C* m2C;
};

void func_0036C1E4(Obj36C0* p) {
    Elem44 e = data_00708AA0[(u8)p->m1c];
    Vec3 pos;
    if (p->m28) pos.setCopy(*p->m28);
    else pos.setCopy(p->m4->pos);
    if (p->m2C) p->m2C->f0(&e, &pos);
    func_001E8268(data_00708998->m18, (char*)p->mC + 0xac, &pos, &e);
}
