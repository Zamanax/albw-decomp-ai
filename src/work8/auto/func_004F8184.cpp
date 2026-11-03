typedef unsigned int u32;
typedef float f32;
f32 func_004F8184(u32 n, f32 d, f32 b, f32 c) {
    f32 sum = 0.0f;
    f32 t = sum;
    for (u32 i = 0; i < n; ++i) {
        t -= d;
        sum += t;
    }
    return (c - sum - b) / (f32)n;
}
