#include "albw_types.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 func_004F8254(void* a, void* b);

u32 func_00265B48(u8* self, u8* r1) {
    u8* q = *(u8**)(self + 0x430);
    u16 z = 0;
    u16* pz = &z;
    *(u16*)(q + 0x28) = *pz;
    if (*(u32*)(self + 0x910) == *(u32*)(self + 0x3a0)) {
        s32 k = *(s8*)(*(u8**)(r1 + 0x2c) + 1);
        if (k == 10 || k == 9 || k == 7) {
            u8* f = *(u8**)(self + 0x430);
            u16 v = 0xa0;
            *pz = v;
            *(u16*)(f + 0x28) = *pz;
        }
    }
    return func_004F8254(self, r1);
}
