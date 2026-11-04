typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;
typedef float f32;

s16 func_00171744(u32 d) {
    u32 q = d / 60;
    u32 r = d - q * 60;
    f32 v = (f32)(r * 100) / 60.0f;
    s32 n = (s32)v;
    if ((f32)n != v && 0.0f <= v) n++;
    return (s16)n;
}
