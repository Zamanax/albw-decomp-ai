typedef unsigned int u32;
typedef float f32;

struct Timer2FBD {
    u32 cur;
    u32 max;
    f32 rate;
    void start(u32 n, u32 c = 0) { max = n; if (n) rate = 1.0f / n; else rate = 0.0f; cur = c; }
};

struct S39CA94 {
    char p0[0x3e0];
    f32 f3e0;
    char p3e4[0x3e8 - 0x3e4];
    u32 u3e8;
    char p3ec[0x430 - 0x3ec];
    u32 u430;
    char p434[0x450 - 0x434];
    Timer2FBD t450;
    char p45c[0x4bc - 0x45c];
    f32 f4bc;
};

extern "C" void func_004D80A4(void*, u32, f32);

void func_0039CA94(S39CA94* self) {
    self->t450.start(0x5a);
    self->f4bc = 0.1f;
    func_004D80A4((char*)self + 0x3dc, self->u3e8, 0.1f);
    self->f3e0 = 0.0f;
    self->u430 = 0;
}
