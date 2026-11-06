#include "albw_types.h"
u32 f_003E21EC(u32 x) {
    u32 a = (x >> 1) & 0x55555555;
    u32 b = x - a;
    u32 c = (b & 0x33333333) + ((b >> 2) & 0x33333333);
    c = (c + (c >> 4)) & 0x0f0f0f0f;
    c = c + (c >> 8);
    c = c + (c >> 16);
    return c & 0x3f;
}
