typedef unsigned int u32;
typedef unsigned char u8;
extern u8 ro_006F5988[];
extern u32 func_00564A78(void* res, void* name);

u32 func_0058EA60(u8* self, u32 p1, u32 p2, u32 p3) {
    u8* base = self - 0x34;
    struct { void* vt; u32 s; } name;
    u32 h;
    self = *(u8**)(self + 0xa0);
    if (self != 0) {
        if (self[0x16b] == 0) return (u32)(self + 0x104);
        name.vt = ro_006F5988;
        name.s = p1;
        h = func_00564A78(*(void**)(base + 0xd4), &name);
        if (h != 0xffff)
            return (u32)(*(u8**)(*(u8**)(*(u8**)(base + 0xd4) + 0x24) + 0x14) + h * 48);
    }
    return 0;
}
