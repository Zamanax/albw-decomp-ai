typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u32 w00, w04;
    u32 w08, w0c;
    u32 w10, w14;
} Ctx_005612E4;

u32 func_005612E4(Ctx_005612E4* p, u64* out) {
    Ctx_005612E4 * t5 = p;
    u32 t0 = t5->w08;
    u32 t2 = t5->w14;
    Ctx_005612E4 * t4 = p;
    u64 a = t4->w10 | ((u64)t2 << 32);
    *out = a - (((u64)t4->w0c << 32) | t0);
    return 0;
}
