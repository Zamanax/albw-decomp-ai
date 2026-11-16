typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;

extern u32 func_004F7A60(void* a, void* b);

u32 func_002FAF84(u8* self, u8* src) {
    u32* d = (u32*)(self + 0x900);
    d[0] = ((u32*)src)[1];
    d[1] = ((u32*)src)[2];
    d[2] = ((u32*)src)[3];
    u32 r = func_004F7A60(self, src);
    u32 b;
    if (!(*(u32*)(self + 0x5a4) & 0x2000000) && (*(u32*)(self + 0x5a0) & 0x2000000)) b = 1; else b = 0;
    s8* p = (s8*)(self + 0x910);
    *p = (b | *p) ? 1 : 0;
    u16 s = *(u16*)(src + 0x20);
    u32 one = 1;
    return ((one << (s & 0x1f)) & 0xd80) ? 1 : r;
}
