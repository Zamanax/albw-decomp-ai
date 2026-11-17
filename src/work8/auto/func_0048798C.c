#include "albw_types.h"
extern void func_0066F3FC(void*, s32);
extern void func_001E6CE8(void*);

void func_0048798C(char* self) {
    char* p = *(char**)(self + 0x138);
    if (p != 0 && *(s32*)(p + 8) != 0) {
        s32 idx = *(s16*)(p + 2);
        if (idx >= 0) {
            char* q = *(char**)(self + 0x1c);
            u32 count = *(u32*)(q + 8);
            char* d = *(char**)(q + 0xc);
            char* e = d;
            if (count > (u32)idx) e = d + idx * 56;
            if (*(u8*)(e + 0x35) != 0) return;
        }
    }
    for (s32 i = 0; i < 4; i++) {
        char* slot = self + 0x13c;
        if ((u32)i < 4) slot = slot + i * 4;
        func_001E6CE8(*(void**)slot);
    }
    func_0066F3FC(self + 0xe4, 1);
}
