#include "albw_types.h"

extern char ro_006EFEC0[];

struct S {
    void* vptr;
    u32 a;
    u32 b;
    u32 c;
    f32 value;
    u8 yes;
    u8 pad15[3];
    u32 d;
    u32 e;
    u16 f;
    u16 g;
};

void func_003FF044(S* p)
{
    p->a = 0;
    p->b = 0;
    p->c = 0;
    p->value = 0.0f;
    p->yes = 1;
    p->d = 0;
    p->vptr = ro_006EFEC0;
    p->e = 0;
    S * t0 = p;
    t0->f = 0;
    p->g = 0;
}
