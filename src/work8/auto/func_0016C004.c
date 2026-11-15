extern void func_0016BCBC(void* a0, void* a1, void* a2, void* a3);

typedef struct { unsigned int w[4]; } Blk16;
typedef struct { unsigned int w[3]; } Blk12;
typedef struct { Blk16 a; Blk12 b; } Frame;

void func_0016C004(void* a0, unsigned char* self) {
    Frame f;
    f.a = *(Blk16*)(self + 0x22c);
    f.b.w[0] = *(unsigned int*)(self + 0x1a8);
    f.b.w[1] = *(unsigned int*)(self + 0x1b8);
    f.b.w[2] = *(unsigned int*)(self + 0x1c8);
    func_0016BCBC(a0, &f.a, &f.b, self);
    *(Blk16*)(self + 0x22c) = f.a;
}
