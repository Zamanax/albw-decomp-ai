typedef unsigned int u32;
typedef unsigned char u8;
extern void* data_00712588;
extern u32 func_004A143C(void* p, u32 n);

u32 func_004C403C(void* self, u32 p1) {
    char* s = (char*)self;
    if (*(u32*)(s + 0x10) == 0) return 1;
    u8* fl = (u8*)(s + 0x9b9);
    if (*fl == 0) return 1;
    char* p14 = *(char**)(s + 0x14);
    if (p14[0x1600] != 0) return 1;
    if (*(u32*)((char*)data_00712588 + 0x10) != 0) return 0;
    if (*(u32*)(s + 0x9c0) > 1) return 0;
    u32 off = 0x4be0;
    *(u8*)(s + off) = (u8)p1;
    u32 old = *(u32*)(s + off + 0x1f4);
    char* a = s + 0x4800;
    a = a + 0x3d8;
    u32 r = func_004A143C(a, 0x1fc);
    *(u32*)(a + 0x1fc) = r;
    if (r != old) goto set8;
    return 1;
set8:
    *(u32*)(s + 0x9c0) = 8;
    return 1;
}
