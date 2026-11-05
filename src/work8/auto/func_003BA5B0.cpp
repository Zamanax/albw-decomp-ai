#include "albw_types.h"
extern "C" void func_0038428C(void*, u32, u32);
extern "C" void func_003842C0(void*, u32, u32, u32);

extern "C" void func_003BA5B0(char* self) {
    char* p = *(char**)(self + 0x48);
    u32 q = *(u32*)(p + 0xbcc);
    if (q != 0) ((void (*)(u32))(*(void**)(*(char**)q + 0x14)))(q);
    *(u8*)(self + 0x62) = 0;
    *(u8*)(self + 0x63) = 0;
    char* r = *(char**)(self + 0x48);
    *(u8*)(r + 0x936) = 1;
    *(u16*)(self + 0x90) = 0;
    char* r2 = *(char**)(self + 0x48);
    *(u16*)(0xaf4 + (u32)r2) = 0;
    func_0038428C(r2 + 0x8c0, 0, 1);
    char* r3 = *(char**)(self + 0x48);
    func_003842C0(r3 + 0x8c0, 0x44, 0xa, 1);
    *(u8*)(self + 0x9c) = 1;
}
