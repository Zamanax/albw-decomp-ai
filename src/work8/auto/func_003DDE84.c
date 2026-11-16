#include "albw_types.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    f32 f4;
    f32 f8;
    f32 fc[2];
    u32 w14[2];
    u8 pad1c[8];
    s8 c24[2];
    u8 pad26;
    u8 b27;
    u16 h28;
    u16 h2a;
    u32 w2c;
    u8 f30[2];
    u16 h32;
} EnDDE84;

extern u8 bss_007A06F0[];
extern void func_003DEBDC(void*, f32);
extern void func_003DEDCC(void*, u32, f32);
extern void func_003DE70C(void*, u32, u32);
extern void func_003DEC7C(void*, u32, s32);
extern void func_003DEFE4(void*, u32);
extern void func_003DEB94(void*, u32);
extern void func_003DEC28(void*, u32);
extern void func_003DF844(void*, u32);
extern void func_003DE778(void*, u32);
extern void func_003DF430(void*, u32);
extern void func_003DE6C8(void*, u32);

void func_003DDE84(EnDDE84* p) {
    s32 i;
    f32 v;
    func_003DEBDC(bss_007A06F0, p->f4 * p->f8);
    for (i = 0; i < 2; i++) {
        s8 j = (s8)i;
        s32 flag;
        v = p->fc[j];
        func_003DEDCC(bss_007A06F0, j, v);
        if (p->w14[j] == 0) {
            flag = p->f30[j] != 0;
        } else {
            flag = 1;
        }
        func_003DE70C(bss_007A06F0, j, flag);
        func_003DEC7C(bss_007A06F0, j, p->c24[j]);
    }
    func_003DEFE4(bss_007A06F0, p->b2);
    func_003DEB94(bss_007A06F0, p->b1);
    func_003DEC28(bss_007A06F0, p->h28);
    func_003DF844(bss_007A06F0, p->b27);
    func_003DE778(bss_007A06F0, p->h2a);
    func_003DF430(bss_007A06F0, p->h32);
    p->w2c = 0;
    func_003DE6C8(bss_007A06F0, p->b3);
}
