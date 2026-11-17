#include "albw_types.h"

u32* func_003CC1E4(u32* p, u32 a) {
    if (a & 0xf) {
        u32 t = a << 28;
        t >>= 30;
        s32 n = 4 - (s32)t;
        if (n > 0) {
            u32* d = p - 1;
            u32 z = 0;
            if (n & 1) {
                *++d = z;
            }
            s32 k = n >> 1;
            if (k != 0) {
                do {
                    d[1] = z;
                    k--;
                    d += 2;
                    *d = z;
                } while (k != 0);
            }
            return p + n;
        }
    }
    return p;
}
