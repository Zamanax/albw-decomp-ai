typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;

struct Obj523800 {
    char pad0[0x70];
    u8 b70;
    char pad1[0x2c0 - 0x71];
    u64 v2c0;
    s32 v2c8;
};

u32 func_00523800(struct Obj523800* p) {
    if (p->b70 == 9) return 0;
    {
        u64 a = p->v2c0;
        if (a == (u64)-1) return 0;
        if ((s32)((u32)a - (u32)p->v2c8) < 0) return 0;
        return (u32)(a - (u64)(u32)p->v2c8);
    }
}
