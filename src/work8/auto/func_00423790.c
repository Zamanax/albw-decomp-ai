typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern void* data_007142C8;
extern void* data_0070B728;
extern u32 func_00584B94(void*, s32);
extern s32 func_00576874(void*);
extern s32 func_0058DE90(void*);
extern void func_0066BFFC(void*, s32);

void func_00423790(u8* self) {
    u8* a = *(u8**)(self + 0x14);
    if (!(*(u16*)(a + 0x16) & 8)) return;
    if (*(u32*)(a + 8) != 0) return;
    void* p = data_007142C8;
    s32 r5 = *(s32*)((u8*)p + 0xe8);
    u8* o = *(u8**)(self + 0x5c);
    if (o[0x30c] != 0 || o[0xd0] != 0) return;
    if (func_00584B94(data_0070B728, 0x383) == 0 || data_007142C8 == 0) return;
    if (r5 == 0) return;
    if (func_00576874((void*)r5) == 0) return;
    if (func_0058DE90(data_007142C8) == 0) return;
    func_0066BFFC(self + 0x38, 1);
}
