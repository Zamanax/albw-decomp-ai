typedef unsigned int u32;
extern void func_003F7D78(u32);
extern void func_003F7C78(u32, u32, u32);

void func_002E2F20(char* self) {
    func_003F7D78(*(u32*)(self + 0x10));
    char* q;
    if (*(u32*)(self + 0x2c) > 1) q = *(char**)(self + 0x30) + 8;
    else q = *(char**)(self + 0x30);
    if (*(u32*)(q + 4) == 0) return;
    func_003F7C78(*(u32*)(self + 0x10), 0, 1);
    if (*(u32*)(self + 0x2c) > 1) q = *(char**)(self + 0x30) + 8;
    else q = *(char**)(self + 0x30);
    *(u32*)(q + 4) = 0;
}
