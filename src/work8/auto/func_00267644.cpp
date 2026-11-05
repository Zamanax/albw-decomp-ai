#include "albw_types.h"

struct Pair {
    u32 a;
    u32 b;
};

struct Obj {
    u8 p0[0x3e0];
    f32 vy;
    u8 p1[0x8c8 - 0x3e4];
    u32 st8c8;
    u8 p2[0x9ac - 0x8cc];
    u8 m9ac[0xafc - 0x9ac];
    u32 cnt_afc;
    u32 max_b00;
    u32 pad_b04;
    u32 cnt_b08;
    u32 max_b0c;
    u8 pad_b10[4];
    s8 flag_b14;
};

extern f32 func_004F898C();
extern void func_004F8964(f32* vy, bool clamp, f32 g);
extern bool func_0058A8F0(Obj* p);
extern void func_00268E70(Obj* p);
extern void func_0036B758(void* p);
extern bool func_0036BE78(void* p);
extern void func_00660718(void* p, s32 v) __attribute__((notailcall));

void func_00267644(Obj* p) {
    func_004F8964(&p->vy, true, func_004F898C());
    s8 flag = p->flag_b14;
    if (!func_0058A8F0(p))
        return;
    Pair t8 = *(Pair*)&p->cnt_b08;
    if (t8.b > t8.a) {
        p->cnt_b08 = t8.a + 1;
        return;
    }
    p->flag_b14 = 1;
    if (flag == 0)
        func_00268E70(p);
    Pair ta = *(Pair*)&p->cnt_afc;
    if (ta.b > ta.a) {
        p->cnt_afc = ta.a + 1;
        return;
    }
    func_0036B758(&p->m9ac);
    if (!func_0036BE78(&p->m9ac))
        return;
    func_00660718(&p->st8c8, 0);
}
