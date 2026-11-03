typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

struct Local {
    u32 m0;
    u32 m4;
    u32 m8;
    s32 mC;
    u8 m10;
};

struct Sub {
    char p0[0xc];
    void* m0c;
};

struct Src {
    char p0[0xc];
    Sub* m0c;
    char p1[0x1c - 0x10];
    u32 m1c;
    u32 m20;
};

struct P2 {
    u32 a;
    u32 b;
};

extern "C" u32 func_00110B44(void* a, u32 b, u32 c, u32 d);
extern "C" void func_00110AEC(Local* l);
extern "C" void func_00110988(void* self, Src* s, Local* l);

void func_00110244(void* self, Src* src, P2 p) {
    Local L;
    L.m0 = 0;
    L.m4 = 0;
    L.m8 = 0;
    L.mC = -1;
    L.m10 = 0;
    void* q = src->m0c->m0c;
    L.m4 = func_00110B44(q, p.a, src->m1c, src->m20);
    L.m8 = p.b;
    func_00110AEC(&L);
    func_00110988(self, src, &L);
}
