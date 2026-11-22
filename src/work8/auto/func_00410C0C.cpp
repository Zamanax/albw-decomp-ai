#include "albw_types.h"

extern "C" s32 func_0056AEA0(void*);
extern "C" u32 func_0056AE68(void*);
extern "C" s32 func_0040E74C(void* p, u32 pos, s32 z);
extern "C" s32 func_0040E6E8(void* p, void* buf, u32 size, s32* out);
extern "C" void func_00413628(void*, char*);

int func_00410C0C(u8* a0, char* a1, u32 a2) {
    s32 r7 = func_0056AEA0(a0 + 0x13c);
    u32 r6 = func_0056AE68(a0 + 0x13c);
    if (r7 == -1 || r6 > a2) {
        return 0;
    }
    s32 ok = func_0040E74C(a0 + 0x11c, r7, 0);
    u8* s = a0 + 0x100;
    if (ok == 0) {
        *(u32*)(a0 + 0x180) = *(u32*)(s + 0x34);
        return 0;
    }
    s32 out = 0;
    if (func_0040E6E8(a0 + 0x11c, a1, r6, &out) == 0) {
        *(u32*)(a0 + 0x180) = *(u32*)(s + 0x34);
        return 0;
    }
    if ((u32)out != r6) {
        return 0;
    }
    func_00413628(a0 + 0x13c, a1);
    return 1;
}
