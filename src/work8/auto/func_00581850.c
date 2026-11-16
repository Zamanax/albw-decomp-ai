typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

extern s32 func_0010FBAC(u32 key, u32 arg);

void* func_00581850(u8* self, u32 arg) {
    s32 i;
    for (i = 0; i < *(s32*)(self + 4); i++) {
        u8* e = (*(u8***)(self + 8))[i];
        u32 j;
        if (e == 0) continue;
        if (e[0] != 'S' || e[1] != 'L' || e[2] != 'N' || e[3] != 'K') continue;
        if (*(u32*)(e + 8) != 0x32) continue;
        {
            u8* base = e + (*(u32*)(e + 0xc)) * 4 + 0x10;
            for (j = 0; j < *(u32*)(e + 0xc); j++) {
                u8* p = e + *(u32*)(e + 0x10 + j * 4);
                *(u8**)(p + 0x1c) = base;
                if (func_0010FBAC(*(u32*)(p + 8) + (u32)base, arg) == 0) return p;
            }
        }
    }
    return 0;
}
