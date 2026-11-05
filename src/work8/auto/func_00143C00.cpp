#include "albw_types.h"
extern "C" void func_002DFF7C(void*);
extern "C" u32 func_0019B04C(u32);
extern "C" int func_00581D60(void*);
extern "C" void func_004C43E0(void*, void*);
extern u32 ro_00693210;
extern u32 ro_006A2570[];
extern void* data_0070C8E0;
extern void* data_00706E20;
u32 func_00143C00(char* self) {
    f32 sz = *(f32*)(self + 0x3e8);
    u32* p = (u32*)(self + 0x3d0);
    char buf[0x2c4];
    *(u32*)(buf + 0x20) = 0; *(u32*)(buf + 0x24) = 0; *(u32*)(buf + 0x1c) = 0;
    *(u32*)(buf + 0x48) = 0; *(u32*)(buf + 0x4c) = 0; *(u32*)(buf + 0x2c0) = 0;
    func_002DFF7C(buf);
    for (s32 i = 0; i < 3; ++i) {
        *(u32*)buf = func_0019B04C(ro_00693210);
        *(u16*)(buf + 0x50) = (u16)func_00581D60(data_0070C8E0);
        *(f32*)(buf + 0x20) = sz;
        *(u16*)(buf + 0x2a) = (u16)ro_006A2570[i];
        *(u16*)(buf + 0x2c) = 1;
        *(u32*)(buf + 4) = p[0];
        *(u32*)(buf + 8) = p[1];
        *(u32*)(buf + 0xc) = p[2];
        *(u32*)(buf + 0x4c) = *(u32*)(self + 0x2cc);
        func_004C43E0(data_00706E20, buf);
    }
    return 1;
}
