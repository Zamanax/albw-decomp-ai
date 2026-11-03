typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

u8 func_002AB1CC(u8 a, s32 b, s32 c) {
    if (b == 0 || a == 30) return a;
    if ((u32)(a - 14) > 3) return a;
    f32 v = (f32)(a + b + 1);
    if (v > 17.0f) v = 17.0f;
    s32 i = (s32)v;
    f32 w = (f32)(i - 1);
    f32 lo = (f32)(u32)((c ^ 1) + 14);
    if (w < lo) w = lo;
    return (u8)(s32)w;
}
