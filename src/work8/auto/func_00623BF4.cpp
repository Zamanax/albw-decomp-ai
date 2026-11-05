typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;


#include "vec3.h"


struct Obj {
    u8 pad0[0x2cc];
    u32 m2cc;
    u8 pad2d0[0x3d0 - 0x2d0];
    Vec3 m3d0;
};

struct Blk800 {
    u8 pad0[0x4c];
    u16 m4c;
};


#include "actor.h"


extern "C" void func_00115C70(void*, void*, void*);
extern "C" u32 func_004904CC(f32, f32);

inline void clearSix(Npc* q) {
    q->m904[0] = -1; q->m904[1] = -1; q->m904[2] = -1;
    q->m904[3] = -1; q->m904[4] = -1; q->m904[5] = -1;
}

void req(Npc* q) { void (*fp)(Npc*, s32, s32) = *(void(**)(Npc*, s32, s32))((char*)(*(void**)q) + 0xac); fp(q, q->m854, -1); }

void target(Npc* p, Obj* a1, s32 a2) {
    Blk800* b = (Blk800*)((u8*)p + 0x800);
    if (a2 == 0) {
        if (a1 == 0) {
            b->m4c = 0;
            p->m810 = p->m2cc;
            return;
        }
        p->m810 = a1->m2cc;
        return;
    }
    if (a1 == 0 || p->m858 == 1) return;
    p->gate85f = 1;
    clearSix(p);
    req(p);
    Vec3 out;
    Vec3* src = (Vec3*)((u8*)a1 + 0x3d0); 
    func_00115C70(&out, src, &p->m3d0);
    f32 fx = out.x;
    f32 fz = out.z;
    p->m818 = func_004904CC(fx, fz);
    p->m810 = a1->m2cc;
}
