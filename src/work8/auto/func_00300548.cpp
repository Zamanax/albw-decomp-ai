#include "albw_types.h"

extern "C" char ro_006DE858[];
extern "C" void func_0010F1F8(void*);
extern "C" void* func_004A1520(void*);
extern "C" void* func_001E6CE8(void*);

extern "C" void* func_00300548(char* self) {
    *(void**)self = ro_006DE858;
    char* owner = *(char**)(self + 0x1c);
    char* n = self + 0x10;
    if (owner != 0) {
        *(u32*)(n + 0xc) = 0;
        func_0010F1F8(n);
        *(u32*)(owner + 8) = *(u32*)(owner + 8) - 1;
    }
    return func_004A1520((char*)func_001E6CE8(self + 0xcc) - 0xcc);
}
