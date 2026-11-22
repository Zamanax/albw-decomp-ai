#include "albw_types.h"

extern "C" s32 func_00588BE4(void*);
extern "C" u32 ro_00693120;
extern "C" u32 ro_00693130;
extern "C" u32 ro_006930EC;
extern "C" u32 ro_00693118;
extern "C" u32 ro_0069311C;

extern "C" void func_001206B8(void* self) {
    if (self == 0) {
        return;
    }
    s32 id = func_00588BE4(self);
    if (id == (s32)ro_00693120 || id == (s32)ro_00693130 || id == (s32)ro_006930EC || id == (s32)ro_00693118 || id == (s32)ro_0069311C) {
        *(u32*)((char*)self + 0x2e0) |= 2;
    }
}
