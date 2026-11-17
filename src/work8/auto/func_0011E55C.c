#include "albw_types.h"
typedef unsigned int u32;
typedef unsigned short u16;
typedef int s32;

extern u32 func_00103CBC(const char* s);
extern u32 func_005FEE34(const char* s, u32 h);
extern s32 func_006019B8(char* base, u32 n, u32 sz, u32 h, u32* key);

s32 func_0011E55C(char* self, const char* p) {
    if (self == 0) {
        return -1;
    }
    if (p == 0) {
        return -1;
    }
    u32 key[3];
    u32 h = func_00103CBC(p);
    u32 r3 = func_005FEE34(p, h);
    u32 off = *(u32*)(self + 0x10);
    key[2] = (u32)self;
    key[0] = (u32)p;
    key[1] = h;
    char* base = (char*)(off + (u32)self);
    s32 idx = func_006019B8(base, *(u16*)(self + 6), 8, r3, key);
    if (idx < 0) {
        return -1;
    }
    return (s16)*(u32*)(base + idx * 8 + 4);
}
