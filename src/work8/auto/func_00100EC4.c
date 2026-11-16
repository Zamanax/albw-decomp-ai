#include "albw_types.h"

extern u8 data_00712468[];
extern u8* data_007124F0;
extern u32 data_00712588;
u32 func_00101F80(u32 a);
void func_00101F74(u32 a);

u32 func_00100EC4(void) {
    u8* g = data_00712468;
    if (*(u32*)(g + 8) != 0) {
        if (func_00101F80(*(u32*)(g + 8)) != 0) return 2;
    } else {
        return 2;
    }
    if (data_007124F0 != 0 && data_007124F0[0x673] != 0) {
        if (data_00712588 != 0) func_00101F74(data_00712588);
        return 1;
    }
    u8* sys = *(u8**)g;
    if (sys != 0) {
        u8* c = *(u8**)(sys + 0x1c);
        if (c != 0 && c[0x190] != 0) {
            if (data_00712588 != 0) func_00101F74(data_00712588);
            return 1;
        }
    }
    return 0;
}
