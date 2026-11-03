typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef float f32;

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
    void start(u32 n, u32 c = 0) {
        max = n;
        if (n) rate = 1.0f / n;
        else rate = 0.0f;
        cur = c;
    }
};

struct Random { u32 a, b, c, d; };
struct RandMgr { char _0[0x660]; Random rnd; };
extern RandMgr* data_007124F0;
extern "C" u32 func_00111A64(Random* r);
extern "C" void func_004FC07C(void*, s32, s32, s32);

struct Sub800 { char p0[0xe4]; Timer m0e4; };
struct En2A9CAC {
    char p0[0x3dc];
    f32 m3dc, m3e0, m3e4;
    char p3e8[0x800 - 0x3e8];
    Sub800 m800;
};
inline u32 randMax(Random* r, u32 max) { return ((u64)func_00111A64(r) * max) >> 32; }
extern "C" void func_002A9CAC(En2A9CAC* self) {
    func_004FC07C(self, 0, -1, 0);
    self->m3dc = 0.0f;
    self->m3e0 = 0.0f;
    self->m3e4 = 0.0f;
    Random* r = &data_007124F0->rnd;
    self->m800.m0e4.start(randMax(r, 30) + 90);
}
