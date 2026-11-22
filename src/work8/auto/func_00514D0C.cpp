#include "sead_string.h"

typedef unsigned int u32;
typedef int s32;

extern u32 data_0070FB60;
extern u32 func_005568C8(u32);
extern u32 func_0014E2A0(void*, u32, void*, u32, u32, u32);
extern void func_0066B94C(void*, u32);
extern void func_00150A84(void*, const sead::SafeString&, s32);
extern void func_00512FA4(void*);

void func_00514D0C(void* self) {
    u32 r = func_005568C8(data_0070FB60);
    if (r == 0x4d || r == 0x4e || r == 0x51) {
        func_00512FA4(self);
        return;
    }
    u32 ok = func_0014E2A0(self, *(u32*)((char*)self + 0x4cc), (char*)self + 0x4d4, 0x100, 0, 0);
    if (ok != 0) {
        func_0066B94C((char*)self + 0x48c, 9);
        func_00150A84(self, sead::SafeString("SE_KinSta_GET"), 0);
        return;
    }
    func_00512FA4(self);
}
