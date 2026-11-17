#include "albw_types.h"
extern "C" {
void func_001119F4(unsigned a, unsigned b);
f32 func_00115DC8(void* v);
}
extern char bss_007A96F0[];
extern char ro_006F7500[];
extern char ro_006F5108[];
extern char ro_006F5064[];
char* func_0048B2A8(char* self) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    *(void**)self = ro_006F7500;
    func_001119F4((unsigned)(self + 4), (unsigned)bss_007A96F0);
    *(void**)self = ro_006F5108;
    *(f32*)(self + 0x34) = zero;
    *(f32*)(self + 0x38) = zero;
    *(f32*)(self + 0x3c) = one;
    *(f32*)(self + 0x40) = zero;
    *(f32*)(self + 0x44) = zero;
    *(f32*)(self + 0x48) = zero;
    *(f32*)(self + 0x4c) = zero;
    *(f32*)(self + 0x50) = one;
    *(f32*)(self + 0x54) = zero;
    func_00115DC8(self + 0x4c);
    *(void**)self = ro_006F5064;
    return self;
}
