typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

extern "C" int func_0056AE28(void*);
extern "C" u32 func_0056ADA8(void*);
extern "C" int func_0040E74C(void* p, u32 pos, s32 z);
extern "C" int func_0040E6E8(void* p, void* buf, u32 size, s32* out);
extern "C" void func_0041361C(void*, char*);

int func_00410AFC(u8* a0, char* a1, u32 a2) {
    u32 r8 = (u32)func_0056AE28(a0 + 0x13c);
    u32 r6;
    if ((r6 = func_0056ADA8(a0 + 0x13c)) > a2) {
        return 0;
    }
    s32 ok = func_0040E74C(a0 + 0x11c, r8, 0);
    u8* s = a0 + 0x100;
    if (ok == 0) {
        *(u32*)(a0 + 0x180) = *(u32*)(s + 0x34);
        return 0;
    }
    s32 out = 0;
    if (func_0040E6E8(a0 + 0x11c, a1, r6, &out) == 0) {
        *(u32*)(a0 + 0x180) = *(u32*)(s + 0x34);
        return 0;
    }
    if ((u32)out != r6) {
        return 0;
    }
    func_0041361C(a0 + 0x13c, a1);
    return 1;
}
