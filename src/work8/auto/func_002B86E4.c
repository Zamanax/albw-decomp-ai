typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef signed char s8;
extern void func_003A2F8C(void*, s32);
extern void func_003A2FB0(void*, s32);

void func_002B86E4(u8* self) {
    s8* s = *(s8**)(self + 0x8bc);
    u8 e = (u8)s[0xe];
    u32 t = 0x1488;
    *(u8*)(t + (u32)self) = e;
    u8 f = (u8)s[0xf];
    *(u8*)((t | ((s32)t >> 12)) + (u32)self) = f;
    func_003A2F8C(self + 0xbc8, s[0xc]);
    func_003A2FB0(self + 0xbc8, (*(s8**)(self + 0x8bc))[0xd]);
}
