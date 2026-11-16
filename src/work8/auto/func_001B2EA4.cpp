#include "sead_string.h"

extern void func_004FABDC(void*, int, int, int);
extern void func_00150A84(void*, const sead::SafeString&, s32);
extern s32 func_004FB208(void*, int, int, int, int);
extern void func_0065B158(void*, int);

void func_001B2EA4(void* self) {
    char* p = (char*)self;
    *(f32*)(p + 0x3dc) = 0.0f;
    *(f32*)(p + 0x3e0) = 0.0f;
    *(f32*)(p + 0x3e4) = 0.0f;
    func_004FABDC(self, 4, 2, 0);
    func_00150A84(self, sead::SafeString("SE_Stalfos_LAND"), 0);
    *(f32*)(p + 0x4f0) = 1.0f;
    if (func_004FB208(self, 1, 0, 0, 0)) {
        *(f32*)(p + 0x3dc) = 0.0f;
        *(f32*)(p + 0x3e0) = 0.0f;
        *(f32*)(p + 0x3e4) = 0.0f;
        func_0065B158(p + 0x8bc, 9);
    }
}
