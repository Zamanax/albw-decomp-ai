typedef unsigned char u8; typedef unsigned int u32; typedef int s32; typedef short s16; typedef float f32;
extern s32 func_001B6CE4(u8 *p);
extern void func_00462924(u8 *p);
extern void func_00231524(u8 *p);

s32 func_00462800(u8 *p)
{
    s32 r = func_001B6CE4(p);
    u8 b81 = p[0x81];
    if (b81 && p[0x80] != 0) {
        func_00462924(p);
    } else if (p[0x80] == 0) {

        {
            u8 *obj = *(u8 **)(p + 0x1c);
            s32 idx = *(s16 *)(p + 0x2e);
            u8 *ent = *(u8 **)(obj + 0xc);
            if ((u32)*(s32 *)(obj + 8) > (u32)idx) ent += idx * 56;
            if (*(s32 *)(ent + 0x14) >= 0x3f800000) func_00462924(p);
        }

    }

    {
        f32 z = 0.0f;
        f32 f = *(f32 *)(p + 0x8c);
        if (!(z > f)) {
            u32 u = (u32)f;
            if (u <= *(u32 *)(p + 0x90)) {
                func_00231524(p + 0x2c);
                r = 1;
            }
        }
    }
    (*(u32 *)(p + 0x90))++;
    return r;
}

