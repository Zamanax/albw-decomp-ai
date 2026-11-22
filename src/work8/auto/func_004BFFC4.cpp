typedef unsigned char u8;
typedef signed char s8;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

extern "C" void func_001E6778(void* p, void* self, u32 a, u32 b, u32 c, f32 f);

struct Sub {
    u8 p0[0x34];
    f32 m34;
    u8 p1[0x5c - 0x38];
    s8 m5c;
    u8 p2[0xb4 - 0x5d];
    f32 mb4;
    f32 mb8;
};

struct S {
    u8 p0[0x3dc];
    f32 m3dc;
    f32 m3e0;
    f32 m3e4;
    u8 p1[0x7eb - 0x3e8];
    u8 m7eb;
    u8 p2[0x852 - 0x7ec];
    u8 m852;
    u8 m853[3];
    u8 m856;
    u8 p3[0x8ac - 0x857];
    u32 m8ac;
    void f(u32 a, u32 b);
};

void S::f(u32 a, u32 b) {
    f32 z = 0.0f;
    Sub* q = (Sub*)((u8*)this + 0x800);
    q->m34 = z;
    if (m852 != q->m5c) {
        S* t = this;
        void (*fp)(S*, u32, s32) = *(void (**)(S*, u32, s32))((char*)(*(void**)t) + 0xac);
        fp(t, t->m856, -1);
    }
    f32 g = (m852 == q->m5c) ? q->mb8 : q->mb4;
    func_001E6778((u8*)this + 0x7c4, this, a, b, 1, g);
    m7eb = (u8)(1 & ~(m8ac >> 13));
    m3dc = z;
    m3e0 = z;
    m3e4 = z;
}
