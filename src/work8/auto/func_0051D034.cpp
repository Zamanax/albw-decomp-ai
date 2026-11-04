typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Random;
u32 func_00111A64(Random* r);
inline f32 randF(Random* r, f32 m) { return func_00111A64(r) * 2.3283064e-10f * m; }

f32 func_0051D034(Random* r, f32 range) {
    f32 sum = 0.0f;
    for (s32 i = 0; i < 3; i++) sum += randF(r, range);
    f32 v = sum * (1.0f / 3.0f);
    if (v < 0.0f) v = 0.0f;
    else if (v > range) v = range;
    return v;
}
