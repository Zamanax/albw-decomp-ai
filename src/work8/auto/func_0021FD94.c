#include "albw_types.h"
extern void func_0036BE78(void* p);
extern void func_0036B758(void* p);
extern void func_0065E398(void* p, s32 n);
void func_0021FD94(u8* self) {
    func_0036BE78(self + 0x8e8);
    u32 cur = *(u32*)(self + 0xa68);
    u32 max = *(u32*)(self + 0xa6c);
    if (cur < max) {
        *(u32*)(self + 0xa68) = cur + 1;
    } else {
        *(u8*)(self + 0x8e4) = 2;
        *(u8*)(self + 0xaff) = 0;
        func_0036B758(self + 0x8e8);
        func_0036BE78(self + 0x8e8);
        func_0065E398(self + 0x8c0, 5);
    }
}
