typedef unsigned int u32;

extern u32 func_00569658(void* p);
extern u32 func_0056D6B0(void* out, void* a, void* b, u32 c);
extern void* func_00414FF0(u32 x);
extern void func_001E6CE8(void* p);

u32 func_0040B738(char* self, char* base, u32 idx, int c) {
    u32 tmp;
    char* p = *(char**)(self + 4);
    void* q = *(void**)(p + 4);
    if (q) { if (func_00569658(q)) {
        func_001E6CE8(&tmp);
        char* t = base + (idx << 4);
        void* b = t + 0xf4;
        u32 r = func_0056D6B0(&tmp, (base + ((idx * 3) << 2) + 0x134), b, c);
        char* o = (char*)(func_00414FF0(r));
        *(u32*)(o + 0x1fc) = *(u32*)(o + 0x1fc) + 1;
        func_001E6CE8(&tmp);
        return r;
    } }
    return 0;
}
