#include "vec3.h"
extern "C" int func_004904CC(float, float);
struct Q { char pad[8]; Vec3 v; };
struct P { char pad[0x20]; Q* q; int v24; };
struct S { char pad[0x228]; short t; char pad2[0x72]; unsigned char f; unsigned char g; };
extern "C" int func_005549BC(S* self, P* p) {
    if (self->f == 0) {
        if (self->t < 0) return p->v24;
        if (self->g == 2) return 0;
        return (int)0x80000000;
    }
    Vec3* d = &p->q->v;
    int r = func_004904CC(d->x, d->z);
    if (self->f == 1) return r;
    if (self->f == 2) return 0;
    return (int)0x80000000;
}
