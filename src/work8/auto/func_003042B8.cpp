typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
struct Timer {
    u32 cur, max; f32 rate;
    void start(u32 n, u32 c = 0) { max = n; if (n) rate = 1.0f / (f32)n; else rate = 0.0f; cur = c; }
};
struct C {
    char pad0[0x48];
    f32 m48;
    char pad1[0x494 - 0x4c];
    u8 m494;
    char pad2[0x4e4 - 0x495];
    Timer mTimer;
    char pad3[0x518 - (0x4e4 + 12)];
    u8 m518;
    void f();
};
void func_001E4090(C* self, s32 a);   // 0x1E4090
void func_001E405C(C* self, s32 a);   // 0x1E405C
f32 func_0052F864(C* self);           // 0x52F864
void func_002E01FC(C* self);          // 0x2E01FC
void C::f() {
    m494 = 1;
    if ((s32)m48 != 1) m518 = 1;
    func_001E4090(this, 0);
    func_001E405C(this, 0);
    Timer* t = &mTimer;
    u32 n = (u32)func_0052F864(this);
    t->start(n);
    func_002E01FC(this);
}
