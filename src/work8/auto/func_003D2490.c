#include "albw_types.h"

extern u32 func_00108630(void* p, u32 n, u32 tag);
extern void func_0010AC24(u32 result, u32 pc);

static inline void diagnose(u32 r, u32 pc) {
    u32 b = r >> 31; if (b) func_0010AC24(r, pc);
}

void func_003D2490(u8* self) {
    u16 buf[2];
    diagnose(func_00108630(self, 4, 0xb0000), __current_pc());
    diagnose(func_00108630(self + 4, 0x800, 0xb0001), __current_pc());
    diagnose(func_00108630(self + 0x804, 0x800, 0xb0002), __current_pc());
    diagnose(func_00108630(buf, 4, 0xb0003), __current_pc());
    *(u16*)(self + 0x1004) = buf[0];
    *(u16*)(self + 0x1006) = buf[1];
}
