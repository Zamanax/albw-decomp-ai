typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;

extern void* func_0056ABDC(void* p);
extern u8* func_0056AC2C(void* p, u32 idx);

u32 func_0056C890(u8* self, u8* out, u32 idx) {
    u8* a = (u8*)func_0056ABDC(*(void**)(self + 4));
    if (a == 0)
        return 0;
    if ((s32)*(u32*)a <= (s32)idx)
        return 0;
    u8* e = func_0056AC2C(a, idx);
    out[0] = e[0];
    out[1] = e[1];
    out[2] = e[2];
    out[3] = e[3];
    u8* p = (u8*)*(u32*)(e + 8);
    u32 n = *(u32*)(p + (u32)e) & 0xff;
    out[4] = (u8)n;
    u32 m = n > 2 ? 2 : n;
    for (u32 i = 0; i < m; i++) {
        u8* q = (u8*)(*(u32*)(e + 8) + e);
        out[5 + i] = q[4 + i];
    }
    return 1;
}
