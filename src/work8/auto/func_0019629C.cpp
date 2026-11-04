typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef unsigned char u8;
typedef float f32;


#include "vec3.h"


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
u32 func_00111A64(Random* r);
inline u32 randU32(Random* r, u32 max) { return ((u64)func_00111A64(r) * max) >> 32; }
void func_00196330(struct En202* e, u32 b);

struct En202 {
    char p0[0x3dc];
    Vec3 m3dc;          // 0x3dc
    char p3e8[0x440 - 0x3e8];
    u8 m440;            // 0x440
    char p441[0x468 - 0x441];
    Timer m468;         // 0x468
    void f();
};

void En202::f() {
    m3dc.setZero();
    u32 b = m440; if (b) b = 1; func_00196330(this, b);
    m468.start(randU32(&data_007124F0->rnd, 60) + 120);
}
