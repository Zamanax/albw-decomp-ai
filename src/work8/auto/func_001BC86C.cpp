#include "albw_types.h"

extern "C" void* func_004EE484(void*);
extern "C" void* func_004EDC9C(void*);
extern u8 ro_0069E794[];
extern u8 ro_006F7CF8[];

void func_001BC86C(u8* p)
{
    u32 z = 0;
    *p = (u8)z;
    *(u32*)(p + 4) = z;
    *(u32*)(p + 8) = z;
    p += 0xc;
    *(u32*)p = z;
    p = (u8*)func_004EE484(p + 4) + 0x64;
    p = (u8*)func_004EDC9C(p) - 0x74;
    u8* s = ro_0069E794;
    u8* q = p + 0xbc;
    *(u32*)(p + 0xc0) = z;
    *(u64*)(q + 8) = *(u64*)(s + 0x10);
    *(void**)q = ro_006F7CF8;
    *(u32*)(p + 0xcc) = z;
    *(u8*)(p + 0xd4) = (u8)z;
}
