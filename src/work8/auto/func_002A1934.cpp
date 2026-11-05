// MATCH 31/31 (family twin 002A1934 is byte-identical).
// Probe chain: a `Vec3 t = *q` copy from a *pointer local* is what emits the
// add/ldm{r1,r2}/ldr r0,[r4,#0x968]/str [sp,#8]/stm split; copying
// *(Vec3*)((char*)p+0x960) or p->v960 directly merges it into one 3-word ldm.
// The trailing `if` needs -Ono_tailcall (otherwise func_00661FE4 becomes a `b`).
#include "vec3.h"

extern void func_001512B4(void*, const Vec3*);
extern bool func_0058A8F0(void*);
extern void func_00661FE4(void*, int);

struct S2A07 {
    char pad0[0x3d0];
    Vec3 v3D0;
    char pad1[0x938 - 0x3d0 - sizeof(Vec3)];
    char m938;
    char pad2[0x95c - 0x939];
    void* m95C;
    Vec3 v960;
};

void func_002A0714(S2A07* p) {
    Vec3* d = &p->v960;
    d->x = p->v3D0.x;
    d->y = p->v3D0.y;
    d->z = p->v3D0.z;
    if (p->m95C) {
        Vec3* q = &p->v960;
        Vec3 t = *q;
        func_001512B4(p->m95C, &t);
    }
    if (func_0058A8F0(p)) func_00661FE4(&p->m938, 7);
}
