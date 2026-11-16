#include "sead_string.h"
extern void* data_00709D28;
extern void func_004A8304(void*, u32);
extern void func_00150A84(void*, const sead::SafeString&, s32);
void func_001C2FE4(void* self) {
    *(f32*)((char*)self + 0x7f0) = 1.0f;
    func_004A8304(data_00709D28, *(u32*)((char*)self + 0x7bc));
    func_00150A84(self, sead::SafeString("SE_Signboard_BURN"), 0);
}
