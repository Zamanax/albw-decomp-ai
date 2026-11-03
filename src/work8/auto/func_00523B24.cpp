typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;
typedef float f32;

struct Obj523B24 {
    char _pad[0x2dc];
    u32 m2dc;
};

s32 func_00523B24(Obj523B24* self) {
    u32 x = self->m2dc;
    if (x == (u32)-1) return 0;
    u32 k = 100;
    u32 r = x - (x / 60) * 60;
    f32 v = (f32)(r * k) * (1.0f / 60.0f);
    s32 t = (s32)v;
    if ((f32)t == v) return (s16)t;
    if (v >= 0.0f) t++;
    return (s16)t;
}
