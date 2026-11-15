typedef unsigned int u32;
extern void func_003B2718(void* p);

u32 func_003AC318(void* self) {
    char* s = (char*)self;
    char* p = (char*)self + 4;
    u32 cur = *(u32*)p;
    p += 0x400;
    p += 0x138;
    if (cur == (u32)p) return 0;
    *(u32*)(p + 0x90) = *(u32*)(*(u32*)s + 0xb10);
    *(u32*)(s + 4) = (u32)p;
    func_003B2718(p);
    return 1;
}
