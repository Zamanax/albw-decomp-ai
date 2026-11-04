typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
struct Timer {
    u32 cur, max; f32 rate;
    void start(u32 n, u32 c = 0) { max = n; if (n) rate = 1.0f / (f32)n; else rate = 0.0f; cur = c; }
};
struct Sub {
    char p0[0x7c];
    u32 m7c;
    char p1[0x94 - 0x80];
    u8 m94;
    char p2[0xbc - 0x95];
    u8 mbc;
    char p3[0xc5 - 0xbd];
    u8 mc5;
    char p4[0xe4 - 0xc6];
    Timer timer;
};
struct C {
    char pad0[0x2e];
    s16 m2e;
    char pad1[0x400 - 0x30];
    Sub sub;
    char pad2[0x510 - (0x400 + sizeof(Sub))];
    u32 m510;
    u8 m514;
};
void func_001E4090(C* self, s32 a);            // 0x1E4090
void func_001E405C(C* self, s32 a);            // 0x1E405C
void func_001E43F8(C* self, f32 v);            // 0x1E43F8
void func_001E43DC(C* self, f32 v);            // 0x1E43DC
f32 func_0052F864(C* self);                    // 0x52F864
void func_004CF478(void* p, u32 a, u32 b);     // 0x4CF478
extern "C" void func_003325A0(C* self) {
    self->sub.m94 = 0;
    Sub* s = &self->sub;
    if (s->mbc == 0) {
        if (s->mc5 != 1) self->m514 = 1;
    }
    func_001E4090(self, 1);
    func_001E405C(self, 1);
    func_001E43F8(self, 1.0f);
    func_001E43DC(self, 1.0f);
    Timer* t = &self->sub.timer;
    u32 n = (u32)func_0052F864(self);
    t->start(n);
    func_004CF478((void*)self->sub.m7c, 1, 0);
    if (self->m2e != 5 && self->m2e != 6) self->m510 = 0;
}
