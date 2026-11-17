#include "sead_string.h"
#include "albw_types.h"
#include "timer.h"

extern "C" void func_00150A84(void*, const sead::SafeString&, s32);
extern "C" void func_004A8BFC(void*, void*, s32);
extern void* data_00709D28;

extern "C" void func_0024F1D0(char* self) {
    func_00150A84(self, sead::SafeString("SE_SandPillar_SMOKE"), 0);
    u8 f = *(u8*)(self + 0x4b8);
    char* p = self + 0x400;
    func_004A8BFC(data_00709D28, p + 0x1c, f);
    *(u8*)(self + 0x4d9) = 1;
    ((Timer*)(self + 0x4c0))->start(0x19);
}
