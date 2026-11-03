#include "../../work7/ds6/ds6.h"

struct Heap;
void* func_0010CEE0(u32 size, Heap* h, s32 align);
void func_001164F4(void* p, u32 n);

extern char ro_006F7FD8[];

struct Obj4A2704 { void* m0; u32 m4; void* m8; u32 mC; };

Obj4A2704* func_004A6D24(Obj4A2704* self, u32 a, Heap* h, u32 n) {
    void** pv = (void**)self;
    *pv = ro_006F7FD8;
    self->mC = a;
    self->m4 = n;
    void* p = func_0010CEE0(n * 4, h, 4);
    self->m8 = p;
    func_001164F4(p, n * 4);
    return self;
}
