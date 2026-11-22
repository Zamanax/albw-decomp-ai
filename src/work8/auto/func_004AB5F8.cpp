typedef unsigned int u32;
typedef unsigned char u8;

extern "C" {
extern char data_00709DF8[];
extern void func_0058FA08(void*);
extern void func_001BAAF4(void*, int);
}

static inline char* adv(char* p, u32 off) { return p + off; }

extern "C" void func_004AB5F8(char* self)
{
    u32* g = (u32*)(adv(self, 0x7400) + 0x29C);
    if (g[1] != 0) {
        func_0058FA08((void*)g[1]);
        g[1] = 0;
        g[0] = 0;
    }
    u32* q = (u32*)(adv(self, 0x7400) + 0x284);
    q[3] = 0;
    q[2] = 0;
    char* game = *(char**)data_00709DF8;
    func_001BAAF4(*(void**)(self + 0x40), (int)*(signed char*)(game + 0x18));
    u32* h = (u32*)(adv(self, 0x7400) + 0x2AC);
    u32 n = h[0];
    u32** it = (u32**)h[2];
    u32** end = it + n;
    for (; it != end; it++) {
        u32* r5 = (u32*)((char*)*it + 4);
        if (*(void**)((char*)r5 + 4) != 0) {
            func_0058FA08(*(void**)((char*)r5 + 4));
            r5[1] = 0;
            r5[0] = 0;
        }
    }
    h[0] = 0;
    *(u8*)adv(adv(self, 0x7A00), 0xBE) = 0;
}
