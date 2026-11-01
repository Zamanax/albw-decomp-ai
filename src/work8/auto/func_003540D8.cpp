#include "albw_types.h"
struct Sub510 { char pad[4]; u8 m4; };
struct EffOwner { char p0[4]; s32 m4; char p8[0xc - 8]; u32 mc; char p10[0x280 - 0x10]; u8 m280; };
struct Eff { char p0[0x1c]; u32 m1c; EffOwner* m20; u32 m24; char p28[0x3c - 0x28]; u32 m3c; };
struct EffHandle { Eff* p; u32 id; };
inline void effFadeImpl(Eff* e, u8 v) {
    EffOwner* o = e->m20;
    if (o && e->m24 == o->mc && o->m4 > 0) o->m280 = v;
    e->m3c &= ~4;
    e->m3c |= 8;
}
inline bool effIsValid(const EffHandle* h) { if (h->p == 0) return false; const u32& id = h->id; return h->p->m1c == id; }
inline void effFade(EffHandle* h) { if (effIsValid(h)) effFadeImpl(h->p, 1); }

struct En {
    char p0[0x508];
    s16 m508;
    char p50a[0x510 - 0x50a];
    Sub510* m510;
    char p514[0xa28 - 0x514];
    u32 ma28;
    u32 ma2c;
    char pa30[0xa5c - 0xa30];
    u32 ma5c;
    char pa60[0xa61 - 0xa60];
    s8 ma61;
    char pa62[0xa80 - 0xa62];
    EffHandle ma80;
    void f();
};
void func_00355C50(En* e);
void func_00666318(void* p, s32 v);

void En::f() {
    func_00355C50(this);
    s8 st = ma61;
    if (st == 8) {
        u32 a = ma28;
        u32 b = ma2c;
        if (a < b) ma28 = a + 1;
    }
    if (m510->m4 != 0) return;
    if (m508 <= 0) {
        effFade(&ma80);
        func_00666318(&ma5c, 9);
        return;
    }
    if (st == 8) func_00666318(&ma5c, 8);
    else if (st == 6 || st == 7) func_00666318(&ma5c, st);
    else func_00666318(&ma5c, 3);
}
