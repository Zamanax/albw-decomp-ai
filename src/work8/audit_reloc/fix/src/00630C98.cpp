
typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
struct Npc;
struct Blk800 {
    u8 p0[0x3c]; u32 m3c; u8 p1[0x4c - 0x40]; u16 m4c; u16 m4e;
    u8 p2[0x5d - 0x50]; u8 m5d;
};

#include "actor.h"

extern "C" void* data_00709D28;
extern "C" void func_004A8304(void*, u32);
extern "C" void func_004A879C(void*, u32, s32);
extern "C" void func_001E6A3C(Npc*);
extern "C" void func_004C07D8(Npc*);
extern "C" void func_00630BA8(Npc*, s32, s32);
u32 getId(Npc* p) { return p->m86c; }
void target(Npc* p) {
    Blk800* b = (Blk800*)((char*)p + 0x800);
    if (b->m5d == 0) return;
    if (p->m85a == 3 && p->m858 != 0) {
        void* const& g = data_00709D28;
        func_004A8304(g, getId(p));
        func_004A879C(g, getId(p), 3);
    }
    func_001E6A3C(p);
    p->m3ac = b->m3c;
    func_004C07D8(p);
    p->m810 = 0;
    p->m85d = 0;
    b->m4c = 0;
    b->m4e = 0;
    if (p->m964 == 2 && (p->m8ac & 0x20) != 0 && (p->m8ac & 0x10) == 0 && p->m857 == 0) {
        func_00630BA8(p, 3, 0);
        return;
    }
    func_00630BA8(p, p->m984, 0);
}
