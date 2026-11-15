#include "albw_types.h"
extern "C" void func_004CF478(void*, u32, u32);
extern "C" void func_002E01FC(void*);
extern "C" void func_006657B4(void*, u32);
extern "C" void func_00332710(void* self) {
    func_004CF478(*(void**)((u8*)self + 0x47c), 0, 0);
    func_002E01FC(self);
    if (*((u8*)self + 0x517) == 0) {
        if ((s32)*(f32*)((u8*)self + 0x48) == 2 || (s32)*(f32*)((u8*)self + 0x48) == 3) {
            func_006657B4((u8*)self + 0x4c0, 1);
        }
    }
}
