#include "../../work7/ds2/ds2.h"
extern void func_00435BE8(void*, void*);
extern void* g_709D28;
extern void func_004A9120(void*, void*);
extern void func_004A8BFC(void*, void*, u32);
void func_0014EE44(void* a0, char* a1, char* a2) {
    if (a2 == 0) return;
    char* p = a1;
    *(char**)((char*)a0 + 0x3a0) = a2;
    if (p == 0 || *(u32*)(p + 0x4c) == 0) return;
    u8 old = *(u8*)(p + 0x20);
    func_00435BE8(p + 0x20, a2);
    u8 n = (u8)(*(u16*)(a2 + 4) & 0xff);
    if (old == n) return;
    *(u8*)(p + 0x20) = n;
    func_004A9120(g_709D28, p);
    func_004A8BFC(g_709D28, p, n);
}
