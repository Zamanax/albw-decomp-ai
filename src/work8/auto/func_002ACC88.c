typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef struct { u32 a, b, c; } Blk;
typedef struct { Blk head; char pad[24]; s8 k; u8 b25; u8 pad26; u8 f27; u8 b28; } S;
extern void func_0014FC2C(void*, u32);
extern void func_0014FAE0(void*);
extern void func_0014FF58(void*, u32);
void func_002ACC88(S* self) {
    u32 f = self->f27;
    Blk h = self->head;
    if (f) f = 1;
    switch (self->k) {
    case 0:
    case 8:
        if (self->b25 != 1 && f != 0) func_0014FAE0(&h);
        return;
    case 5:
    case 0x10: {
        u32 b = self->b28;
        if (f != 0) func_0014FC2C(&h, b);
        else func_0014FF58(&h, b);
        return;
    }
    default:
        return;
    }
}
