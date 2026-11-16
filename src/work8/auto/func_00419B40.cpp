typedef unsigned int u32;

extern "C" void func_004149E4(void*);
extern "C" void func_0041497C(void*);

int func_00419B40(char* self, int lim) {
    if (*(u32*)(self + 4) == 0) return 0;
    char* p = *(char**)(self + 8) - 0x58;
    if (*(int*)(p + 0x40) > lim) return 0;
    u32 r7 = *(u32*)(p + 8);
    void (*fn)(void*, int, u32) = *(void (**)(void*, int, u32))(p + 0xc);
    u32 arg = *(u32*)(p + 0x10);
    func_004149E4(p);
    func_0041497C(p);
    if (fn) fn(p, 2, arg);
    return (int)r7;
}
