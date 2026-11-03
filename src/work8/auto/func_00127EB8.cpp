typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;

extern "C" void func_006568D8(void*, int) ;

void func_00127EB8(u8* self) {
    if (*(u8*)(*(u32*)(self + 0x510) + 4) != 0) return;
    u8* p = self + 0x8bc;
    s16 v = *(s16*)(self + 0x508);
    if (v <= 0) {
        func_006568D8(p, 4);
        return;
    }
    if (self[0x90c] != 0) {
        func_006568D8(p, 7);
        return;
    }
    if (*(u8*)(*(u32*)(self + 0x510) + 5) != 6) {
        func_006568D8(p, 5);
        return;
    }
    self[0x920] = 1;
    func_006568D8(p, 2);
}
