typedef unsigned int u32; typedef unsigned short u16; typedef int s32; typedef unsigned char u8; typedef float f32;
struct Pt { s32 p0; f32 y; f32 z; f32 x; char p1[0x20 - 0x10]; u16 h20; };
struct Self { char p0[0x3e8]; s32 a3e8; char p1[0xa64 - 0x3ec]; s32 a64; u8 a68; };
s32 func_004FB220(Self* s, u32 a, u32 b);
s32 func_004F4A68(Self* s, const Pt* p);
s32 func_004905E0(f32);
inline s32 atan2Idx(f32 y, f32 x) {
    if (x == 0.0f && y == 0.0f) return 0;
    if (x >= 0.0f) {
        if (y >= 0.0f) {
            if (x >= y) return func_004905E0(y / x);
            else return 0x40000000 - func_004905E0(x / y);
        } else {
            if (x >= -y) return -func_004905E0(-y / x);
            else return 0xc0000000 + func_004905E0(x / -y);
        }
    } else {
        if (y >= 0.0f) {
            if (-x >= y) return 0x80000000 - func_004905E0(y / -x);
            else return 0x40000000 + func_004905E0(-x / y);
        } else {
            if (x <= y) return 0x80000000 + func_004905E0(y / x);
            else return 0xc0000000 - func_004905E0(x / y);
        }
    }
}
s32 func_00501D50(Self* s, const Pt* p) {
    u32 h = p->h20;
    u32 b = (h & 0x7e0) >> 5;
    if (func_004FB220(s, h & 0x1f, b)) return 0;
    f32 z = p->z;
    z = z > 0.0f ? z : -z;
    if (z < 0.4f) {
        f32 x = p->x;
        f32 y = p->y;
        s32 angle = atan2Idx(y, x);
        s32 base = s->a3e8 + 0x80000000;
        s32 d = (short)((base >> 16) - (angle >> 16));
        f32 fd = (f32)d;
        fd = fd > 0.0f ? fd : -fd;
        s32 m = (s32)fd << 16;
        if (m < 0x60000000) {
            s->a64 += (u32)angle >> 16;
            s->a68 += 1;
        }
    }
    return func_004F4A68(s, p);
}
