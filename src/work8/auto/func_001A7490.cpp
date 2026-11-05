#include "timer.h"
#include "albw_types.h"
extern "C" void func_004FABDC(void*,s32,s32,s32);
extern "C" u32 func_00111A64(void*);
extern "C" void* data_007124F0;
inline u32 below(void* r, u32 n) { return (u32)(((unsigned long long)func_00111A64(r) * n) >> 32); }
struct E {
    char a[0x30];
    u16 h30;
    char b[0x3dc - 0x32];
    f32 f3dc;
    char c[0x3e4 - 0x3e0];
    f32 f3e4;
    char d[0x8c1 - 0x3e8];
    s8 k8c1;
    char e[0x8e8 - 0x8c2];
    Timer t8e8;
    char f[0x936 - 0x8f4];
    u8 b936;
};
void target(E* p) {
    p->f3e4 = 0.0f;
    p->f3dc = 0.0f;
    s8 t0 = p->k8c1;
    s32 k = t0;
    func_004FABDC(p, 0, -1, 0);
    if (k == 6) {
        p->t8e8.start(p->h30 == 0 ? 0xf : 0x3c);
        p->b936 = 1;
        return;
    }
    u32 n = below((u8*)data_007124F0 + 0x660, 0x3c) + 0x3c;
    p->t8e8.start(n);
}
