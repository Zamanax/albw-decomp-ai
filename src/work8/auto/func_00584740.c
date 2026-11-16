typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct { u32 a; u32 b; } Pair8;
typedef struct { u32 a; u32 b; u32 c; } Tri12;
void func_00584740(void* self, void* dst) {
    u8* s = (u8*)self;
    u8* d = (u8*)dst;
    u32 w578 = *(u32*)(s + 0x578);
    *(u16*)(d + 2) = (u16)w578;
    u32 w574 = *(u32*)(s + 0x574);
    *(u32*)(d + 4) = w574;
    u32 w598 = *(u32*)(s + 0x598);
    *(u32*)(d + 8) = w598;
    Pair8 pr = *(Pair8*)(s + 0x56C);
    *(Pair8*)(d + 0xC) = pr;
    Tri12 tr = *(Tri12*)(s + 0x588);
    u32 w594 = *(u32*)(s + 0x594);
    *(u32*)(d + 0x20) = w594;
    *(Tri12*)(d + 0x14) = tr;
}
