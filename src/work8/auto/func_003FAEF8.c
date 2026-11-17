typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

struct R003FAEF8 {
    u8* base;
    u32 n;
};

void func_003FAEF8(struct R003FAEF8* r) {
    u32 i = 0;
    while (i < r->n) {
        *(f32*)(r->base + i * 32 + 8) = 0.0f;
        *(f32*)(r->base + i * 32 + 12) = 0.0f;
        *(u32*)(r->base + i * 32) = 0;
        struct R003FAEF8 * t0 = r;
        *(u32*)(t0->base + i * 32 + 4) = 0;
        i++;
    }
}
