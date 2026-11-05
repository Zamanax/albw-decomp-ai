#include "sead_string.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef float f32;

struct Req5C { Req5C(u16 id, u32 arg, bool flag); u32 m[0x5C / 4]; };
void func_0016898C(void*, const Req5C&);
void func_00150A84(void*, const SafeString&, s32);

struct This00 {
    char pad0[0x3e0];
    f32 m3e0;
    char pad1[0x4b0 - 0x3e4];
    void* m4b0;
    char pad2[0x559 - 0x4b4];
    u8 m559;
};

void func_00514278(This00* t) {
    func_0016898C(t->m4b0, Req5C(6, 6, false));
    t->m3e0 = -0.02f;
    func_00150A84(t, SafeString("SE_KinSta_BOUND"), 0);
    t->m559 = 1;
}
