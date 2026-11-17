#include "albw_types.h"
extern "C" void func_0012C790(void*);
extern "C" void func_0051C2F0(void*);
extern "C" void func_003616D4(void*, s32, s32);
extern "C" void func_0065CD54(void*, s32);
extern "C" void func_005194D8(void*);
extern "C" void func_001B6B38(void*);
extern void* data_007142C8;
extern void* data_0070FB60;

struct Cls0F574 {
    char pad0[0xd];
    unsigned char b0d;
    unsigned char b0e;
    char pad1[0x78 - 0xf];
    unsigned char b78;
    char pad2[0x118 - 0x79];
    signed char s118;
    signed char s119;
    signed char s11a;
    signed char s11b;
};

extern "C" void func_0045F574(Cls0F574* p) {
    if (p->b0d != 0 || p->b0e != 0) {
        if (p->b78 != 3) {
            s32 a2 = p->s118;
            void* o = data_0070FB60;
            s32 a1 = p->s11a;
            func_003616D4(o, a1, a2);
            s32 b2 = p->s119;
            s32 b1 = p->s11b;
            func_003616D4(o, b1, b2);
            void* cfg = data_007142C8;
            func_0065CD54((char*)*(void**)((char*)cfg + 0x130) + 0xc, 2);
            func_005194D8(data_007142C8);
        }
        func_0012C790(p);
        func_0051C2F0(data_007142C8);
        func_001B6B38(p);
    }
}
