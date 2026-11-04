typedef unsigned short u16;
typedef int s32;
typedef float f32;
extern const u16 ro_006BB410[];
static f32 clamp01(f32 t, f32 lo, f32 hi) {
    if (t > hi) t = hi;
    else if (t < lo) t = lo;
    return t;
}
u16 func_00413810(f32 t) {
    t = clamp01(t, 0.0f, 1.0f);
    if (t < 0.13561438f) return 0x50;
    if (t >= 0.9f) return 0x3e80;
    return ro_006BB410[(s32)((t - 0.13561438f) * 29.999998f)];
}
