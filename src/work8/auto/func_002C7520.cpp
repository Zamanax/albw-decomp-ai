typedef unsigned int u32; typedef int s32; typedef unsigned char u8; typedef float f32;
struct Vec3 {f32 x,y,z;};
struct Obj {char p0[8]; Vec3 v; };
extern "C" float sqrtf(float);
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
struct Self { char p0[0x3e8]; s32 a3e8; char p1[0x468 - 0x3ec]; u8 b468; u8 b469; };
struct Pt { s32 p0; f32 y; f32 z; f32 x; };
s32 func_002C7520(Self* s, const Pt* p) {
    f32 z = p->z;
    z = z > 0.0f ? z : -z;
    if (z >= 0.4f) return 0;
    f32 x = p->x;
    f32 y = p->y;
    s32 angle = atan2Idx(y, x);
    s32 base = (s->b468 == 0) ? s->a3e8 + 0x80000000 : s->a3e8;
    s32 d = (short)((base >> 16) - (angle >> 16));
    f32 fd = (f32)d;
    fd = fd > 0.0f ? fd : -fd;
    s32 m = (s32)fd << 16;
    if (m < 0x20000000) s->b469 = 1;
    return 0;
}
