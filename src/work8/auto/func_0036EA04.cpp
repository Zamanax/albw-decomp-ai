#include "vec3.h"

struct Ea04Src {
    char pad[0x3d0];
    Vec3 v;
};

struct Ea04Obj {
    unsigned int m0;
    Vec3 m4;
    char pad10[0x30];
    unsigned int m40;
    unsigned int m44;
    char pad48[0x14];
    float m5c;
    char pad60[4];
    unsigned int m64;
    char pad68[2];
    unsigned char m6a;
    unsigned char m6b;
};
void func_0036EA04(Ea04Obj* o, Ea04Src* s) {
    o->m5c = 0.0f;
    Vec3* q = &s->v; Vec3* d = &o->m4; *d = *q;
    unsigned int c = 0x3c;
    unsigned int z = 0;
    unsigned int k = o->m6a ? 0x2aaaaaaau : 0xaaaaaaaau;
    o->m6b = 1;
    o->m64 = c;
    o->m40 = z;
    o->m44 = k;
}
