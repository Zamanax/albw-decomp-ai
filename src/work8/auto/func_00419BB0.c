typedef unsigned char u8;
typedef unsigned int u32;
extern void func_004149E4(void*);
extern void func_0041497C(void*);
extern void func_003E696C(void*);
extern void func_00414FBC(void*);

void func_00419BB0(u8* p)
{
    if (p[0] == 0) return;
    for (;;) {
        if (*(u32*)(p + 4) == 0) break;
        u32 w = *(u32*)(p + 8);
        u8* o = (u8*)(w - 0x58);
        func_004149E4(o);
        u32 cb = *(u32*)(o + 0xc);
        if (cb != 0) {
            u32 arg = *(u32*)(o + 0x10);
            void (*fp)(void*, u32, u32) = (void (*)(void*, u32, u32))cb;
            fp(o, 1, arg);
        }
        func_0041497C(o);
    }
    for (;;) {
        if (*(u32*)(p + 0x10) == 0) break;
        u8* h = p + 0x10;
        u32 n = *(u32*)(p + 0x14);
        u8* o2 = (u8*)(n - 0x58);
        func_003E696C(h);
        func_00414FBC(o2);
    }
    p[0] = 0;
}
