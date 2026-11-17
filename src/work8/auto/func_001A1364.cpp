#include "flags.h"

typedef unsigned int u32;

extern "C" void func_0036C45C(void* p);

extern "C" void func_001A1364(void* self) {
    char* p = (char*)self;
    char* q = p + 0x1200;
    if (*(unsigned char*)(q + 0x26) != 0) {
        func_0036C45C(p + 0x8c8);
        if (*(u32*)(p + 0x98c) >= *(u32*)(p + 0x990)) {
            ((Flag32*)(p + 0x59c))->reset(1);
        }
        if (*(u32*)(p + 0x9b4) == 6) {
            ((Flag32*)(p + 0x59c))->set(0x2000);
        }
        return;
    }
    if (*(signed char*)(q + 0x1f) >= 0) {
        return;
    }
    u32* c = (u32*)(p + 0x11d4);
    if (c[0] < c[1]) {
        c[0] += 1;
        return;
    }
    ((Flag32*)(p + 0x59c))->set(0x1000);
}
