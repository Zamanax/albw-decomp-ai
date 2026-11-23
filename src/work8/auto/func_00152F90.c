typedef signed int s32;
typedef unsigned char u8;
typedef float f32;

extern s32 func_0051D2F4(s32 *cur, s32 target, f32 rate, s32 a, s32 b);
extern s32 func_0058A8F0(void *self);
extern void func_00657BD4(void *p, s32 v);
extern f32 func_0058AA40(void *self);
extern f32 func_00153528(void *self, f32 a, f32 b, f32 c, f32 d, f32 e);
extern f32 func_001534C0(void *self, f32 a, f32 b, f32 c, f32 d, f32 e);

void func_00152F90(char *self)
{
    s32 bits;
    f32 v;
    f32 out;
    f32 k;

    func_0051D2F4((s32 *)(self + 0x8f4), 0, 0.3f, 0x2d82d82, 0x7fffffff);
    if (func_0058A8F0(self) != 0) {
        func_00657BD4(self + 0x90c, 0);
        return;
    }
    if (*(u8 *)(self + 0x931) != 0) *(u8 *)(self + 0x829) = 1;
    v = func_0058AA40(self);
    k = 1.4f;
    bits = *(s32 *)&v;
    out = 0.5f;
    if (bits > 0x42860000) {
        if (*(s32 *)&v <= 0x429a0000) {
            out = func_00153528(self, k, 0.5f, v, 67.0f, 77.0f);
        } else if (*(s32 *)&v <= 0x42ae0000) {
            out = func_001534C0(self, k, 0.5f, v, 77.0f, 87.0f);
        }
    }
    *(f32 *)(self + 0x574) = out;
}
