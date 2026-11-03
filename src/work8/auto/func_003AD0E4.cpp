#include "../../work7/ds3/ds3.h"
extern "C" void func_002DFF7C(void*);
extern "C" u32 func_0019B04C(u32);
extern "C" u16 func_00581D60(void*);
extern "C" void func_004C43E0(void*, void*);
extern "C" void func_00115DAC(void*, const void*, const void*, float);
extern u32 ro_00693920;
extern void* data_0070C8E0;
extern void* data_00706E20;
void func_003AD0E4(char* self, u32* a1) {
    char buf[0x2c4];
    *(u32*)(buf + 0x20) = 0; *(u32*)(buf + 0x24) = 0; *(u32*)(buf + 0x1c) = 0;
    *(u32*)(buf + 0x48) = 0; *(u32*)(buf + 0x4c) = 0; *(u32*)(buf + 0x2c0) = 0;
    func_002DFF7C(buf);
    *(u32*)buf = func_0019B04C(ro_00693920);
    *(u16*)(buf + 0x50) = func_00581D60(data_0070C8E0);
    *(u32*)(buf + 4) = *(u32*)(self + 0x3d0);
    *(u32*)(buf + 8) = *(u32*)(self + 0x3d4);
    *(u32*)(buf + 0xc) = *(u32*)(self + 0x3d8);
    char* o = buf + 4;
    func_00115DAC(o, self + 0x3dc, o, 2.0f);
    *(u32**)(buf + 0x20) = a1;
    *(u32*)(buf + 0x4c) = *(u32*)(self + 0x2cc);
    func_004C43E0(data_00706E20, buf);
}
