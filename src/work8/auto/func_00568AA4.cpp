typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

#include "sead_math.h"

struct Owner {
    u8 pad0[0x3c];
    f32 m3c;
    f32 m40;
    u8 pad1[0x47 - 0x44];
    u8 m47;
};
void func_00568AA4(Vec4* out, const Owner* self) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    out->w = 0.0f;
    f32 x = 0.0f;
    f32 y = x;
    u8 m = self->m47;
    u32 a = m & 3;
    if (a == 0) {
        x = self->m3c * -0.5f;
    } else if (a == 2) {
        x = -self->m3c;
    }
    u32 b = ((u32)m << 28) >> 30;
    if (b == 0) {
        y = self->m40 * 0.5f;
    } else if (b == 2) {
        y = self->m40;
    }
    out->x = x;
    out->y = y;
    f32 m3c = self->m3c;
    out->z = x + m3c;
    out->w = y - self->m40;
}
