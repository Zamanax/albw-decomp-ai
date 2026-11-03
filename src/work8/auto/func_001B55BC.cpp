#include "../../work7/ds3/ds3.h"
extern "C" void func_0014FDC4(void*, int, int, f32, f32);
extern "C" int func_0058E2B8(u32*);
extern "C" void func_0051D2F4(s32*, int, int, int, f32);
void func_001B55BC(char* self, int a1, int a2, f32 a3) {
    char* p = self + 0x800;
    char* q = self + 0x3e8;
    u32 saved = *(u32*)q;
    q += 0x18;
    f32 v = *(f32*)(q + 0x3a8);
    p += 0xf4;
    f32 s = a3;
    if (v != 0.0f || *(f32*)(q + 0x3b0) != 0.0f) s *= 0.25f;
    *(f32*)(self + 0x3e4) = 0.0f;
    *(f32*)(self + 0x3dc) = 0.0f;
    func_0014FDC4(self, a1, a2, s, 0.1f);
    if (*(void**)p) {
        u32 d;
        u32* pd = &d;
        *pd = *(u32*)(self + 0x3e8) - saved;
        s32 idx = func_0058E2B8(pd);
        s32 m = idx < 0xb60b60 ? 0xb60b60 : idx;
        func_0051D2F4((s32*)p, 0, 0xb60b60, m, 1.0f);
    }
}
