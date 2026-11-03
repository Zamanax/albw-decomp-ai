#include "../../../shared/include/albw_types.h"

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
    void start(u32 n, u32 c = 0) {
        max = n;
        if (n == 0) rate = 0.0f;
        else rate = 1.0f / n;
        cur = c;
    }
};

struct BitFlag32 {
    u32 v;
    void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u32 m) { change(m, true); }
    void reset(u32 m) { change(m, false); }
};

struct Random;
struct En;
u32 func_00111A64(Random* r);
inline u32 randU32(Random* r, u32 max) { return ((u64)func_00111A64(r) * max) >> 32; }
Random* func_0058A7D4(En* e);
void func_004FABDC(En* e, s32 a, s32 b, s32 c);

struct En {
    char p0[0x59c];
    BitFlag32 m59c;     // 0x59c
    char p5a0[0x95c - 0x5a0];
    Timer m95c;         // 0x95c
    Timer m968;         // 0x968
    void f();
};

void En::f() {
    m59c.set(4); m59c.set(0x80);
    m59c.set(1); m59c.set(2);
    m95c.start(randU32(func_0058A7D4(this), 120) + 120);
    m968.start(randU32(func_0058A7D4(this), 40) + 20);
    func_004FABDC(this, 1, -1, 0);
}
