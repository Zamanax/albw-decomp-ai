#include "../../work7/ds2/ds2.h"
struct Req5C { Req5C(u16 id, u32 arg, bool flag); u32 m[0x5C / 4]; };
void func_00151148(void*, u32);
void func_0016898C(void*, const Req5C&);

struct This22 {
    char pad0[0x3dc];
    f32 m3dc;
    f32 m3e0;
    f32 m3e4;
    char pad1[0x4b0 - 0x3e8];
    void* m4b0;
    char pad2[0x520 - 0x4b4];
    void* m520;
};

void func_0051402C(This22* t) {
    func_00151148(t->m520, 1);
    t->m3dc = 0.0f;
    t->m3e4 = 0.0f;
    t->m3e0 = 0.5f;
    func_0016898C(t->m4b0, Req5C(2, 6, false));
}
