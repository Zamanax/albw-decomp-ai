typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32; typedef unsigned long long u64; typedef float f32;

extern u32 func_00111A64(void* r);
extern void* func_0058A7D4(void* a);
extern void func_003B8E10(void* self);

inline u32 randRange(void* r, u32 max) {
    return (u32)(((u64)func_00111A64(r) * max) >> 32);
}

void func_003B8B8C(u8* p) {
    *(u8*)(p + 0x62) = 0;
    *(u8*)(p + 0x63) = 0;
    *(u8*)(*(u8**)(p + 0x48) + 0x918) = 0;
    if (randRange(func_0058A7D4(*(void**)(p + 0x48)), 0x65) > 0x1e) {
        *(u32*)(p + 0x58) = 1;
    } else {
        *(u32*)(p + 0x58) = randRange(func_0058A7D4(*(void**)(p + 0x48)), 3) + 2;
    }
    func_003B8E10(p);
    *(u32*)(p + 0x54) = 0;
    *(f32*)(p + 0x98) = (f32)(s32)randRange(func_0058A7D4(*(void**)(p + 0x48)), 3);
    *(u8*)(*(u8**)(p + 0x48) + 0x936) = 1;
    *(u16*)(p + 0x90) = 0;
}
