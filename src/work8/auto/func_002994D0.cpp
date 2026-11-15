#include "sead_string.h"

extern "C" u32 func_00588BF0(void*, u32);
extern "C" void func_00588C14(void*, u32, u32);
extern "C" void func_00150A84(void*, const sead::SafeString&, u32);
extern "C" void func_0066184C(void*, u32);

extern "C" void func_002994D0(void* self) {
    u16 h = *(u16*)((u8*)self + 0x36);
    if (h == 0) return;
    if (!func_00588BF0(self, 0)) return;
    u8 f = *((u8*)self + 0x46c);
    if (f != 0) return;
    *((u8*)self + 0x46c) = 1;
    func_00588C14(self, 0, 0);
    func_00150A84(self, sead::SafeString("SE_CaveSparkle_FLASH"), 0);
    func_0066184C((u8*)self + 0x400 + 0xc, 1);
}
