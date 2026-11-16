typedef unsigned char u8;
typedef unsigned int u32;

typedef struct { u32 ret; u32 a; } Pair;

extern u32 func_0041D79C(void*, u32, u32, u32);

void func_00417DE4(u8* self, u32 a, u32 b) {
    if (self[0x10] == 0) {
        void* q = self;
        u32 r = func_0041D79C(q, a, b, 0x1b0);
        Pair t;
        t.ret = r;
        t.a = a;
        *(Pair*)(self + 0x14) = t;
        self[0x10] = 1;
        *(u32*)(self + 0x1c) = b;
    }
}
