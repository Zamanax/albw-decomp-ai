typedef unsigned int u32; typedef int s32; typedef short s16; typedef long long s64;
typedef struct In0 { u32 m0; void* m4; } In0;
typedef struct Self { In0* m0; s16 m4; s16 m6; s16 m8; s16 ma; s16 mc; } Self;
extern s32 func_003E63E8(void*, s16*, s32, s32*, s64*, s32*);
extern s32 func_003D55B4(s32, s32, s32, s32);
extern s32 func_003D5148(Self*, s16*);
s32 func_003D4D38(Self* self, s16* pad)
{
    s64 b = -1; s32 c = -1; s32 a;
    In0* p = self->m0;
    func_003E63E8(p->m4, pad, 1, &a, &b, &c);
    if (a <= 0) return 0;
    pad[0] = func_003D55B4(pad[0], self->m8, self->m4, self->m6);
    self->m8 = pad[0];
    pad[1] = func_003D55B4(pad[1], self->ma, self->m4, self->m6);
    self->ma = pad[1];
    pad[2] = func_003D55B4(pad[2], self->mc, self->m4, self->m6);
    self->mc = pad[2];
    func_003D5148(self, pad);
    return 1;
}
