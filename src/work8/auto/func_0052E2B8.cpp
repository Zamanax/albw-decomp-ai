#include "albw_types.h"

extern void* data_00709DF8;
extern void* data_0070B728;
u32 func_00584B94(void* mgr, s32 id);

bool func_0052E2B8(u8* self) {
    if (self[0x6c4] != 0) return false;
    s8 st = *(s8*)((u8*)*(void**)&data_00709DF8 + 0x18);
    u32 idx = (u32)((s32)st - 9);
    bool r = (idx <= 12);
    if (!r) return r;
    if (func_00584B94(*(void**)&data_0070B728, 0xfa) != 0) r = false;
    if (func_00584B94(*(void**)&data_0070B728, 0x136) != 0) r = true;
    return r;
}
