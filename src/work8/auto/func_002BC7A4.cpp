#include "albw_types.h"

extern "C" void* func_002BDDA4(void* self);
extern "C" u32* func_00532554(void* obj, s32 idx);

extern "C" void func_002BC7A4(void* self) {
    void* r = func_002BDDA4(self);
    if (r != 0) {
        u32* d = (u32*)((u8*)self + 0x920);
        u32* s = func_00532554(r, *(s16*)((u8*)self + 0x2e));
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
    u8* p = (u8*)self;
    u32* q = (u32*)(p + 0x920);
    u32* t = (u32*)(p + 0x3d0);
    u32 a = q[0];
    t[0] = a;
    u32 b = q[1];
    t[1] = b;
    t[2] = q[2];
}

