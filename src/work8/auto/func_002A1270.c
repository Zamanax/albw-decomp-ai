#include "albw_types.h"

typedef struct { u8 pad[0x24]; s8 k24; } Q2A1270;
typedef struct { u8 pad[0x988]; u8 f988; } P2A1270;

u32 func_002A1270(P2A1270* p, u32 c, Q2A1270* q) {
    s8 k = q->k24;
    if (k == 1) {
        p->f988 = 1;
        return 0xf;
    }
    if (k == 2) {
        p->f988 = 1;
    } else {
        u32 t = c & 0xff;
        if (t == 0x1e || t - 0xe <= 3) return 0xf;
        if (c == 0xa) {
            p->f988 = 1;
            return 0xf;
        }
    }
    return c;
}
