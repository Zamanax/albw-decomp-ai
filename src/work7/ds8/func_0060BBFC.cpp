typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef float f32;

extern "C" u32 func_00111A64(void*);
extern "C" void* data_007124F0;
inline u32 below(void* r, u32 n) { return (u32)(((unsigned long long)func_00111A64(r) * n) >> 32); }


#include "actor.h"


struct Blk800 {
    u8 pad0[0x34];
    f32 m34;                 // 0x834
    u8 pad38[0x48 - 0x38];
    u16 m48;                 // 0x848
    u16 m4a;                 // 0x84a
    u8 pad4c[0x50 - 0x4c];
    u16 m50;                 // 0x850
};

void target(Npc* p) {
    Blk800* b = (Blk800*)((char*)p + 0x800);
    b->m34 = 0.0f;
    p->request(p->m853, -1);
    u32 r;
    if (b->m4a) r = 0;
    else r = below((u8*)data_007124F0 + 0x660, 0x96) + 0x96;
    b->m48 = r;
    if (p->m911 != 0xff) b->m50 = below((u8*)data_007124F0 + 0x660, 0x12c) + 0x64;
    p->v38();
}
