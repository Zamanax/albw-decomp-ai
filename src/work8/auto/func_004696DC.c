typedef unsigned char u8;
typedef int s32;

struct Obj22 {
    u8 pad0[0xd];
    u8 bd;
    u8 be;
    u8 pad1[0x88 - 0x0f];
    u8 b88;
    u8 pad2[0xa0 - 0x89];
    s32 wa0;
    u8 ba4;
    u8 pad3[0xb0 - 0xa5];
    u8 b0;
};

extern void func_00231448(void*);
extern void func_0012C718(void*);

void func_004696DC(struct Obj22* o)
{
    if (o->b0 == 0 && o->bd == 3 && o->be == 3) {
        func_00231448((char*)o + 0x38);
        func_00231448((char*)o + 0x44);
        struct Obj22 * t0 = o;
        t0->b88 = 0xe;
        t0->wa0 = -1;
        t0->ba4 = 0;
        func_0012C718(t0);
    }
    o->b0 = 0;
}
