struct Sub { unsigned char p0[4]; unsigned char b4; };
struct En {
    unsigned char p0[0x3a0];
    int m3a0;
    unsigned char p1[0x3e0 - 0x3a4];
    float m3e0;
    unsigned char p2[0x4f0 - 0x3e4];
    float m4f0;
    unsigned char p3[0x508 - 0x4f4];
    short m508;
    unsigned char p4[0x510 - 0x50a];
    struct Sub* m510;
    unsigned char p5[0x8e0 - 0x514];
    int m8e0;
    unsigned char p6[0x8f8 - 0x8e4];
    int m8f8;
};

extern "C" void func_004FB064(void*);
extern "C" void func_004FB0D8(void*, float*);
extern "C" void func_00656B60(void*, int) __attribute__((notailcall));
extern "C" int func_00521040(void*);
extern "C" void func_0012B608(struct En* p) {
    func_004FB064(p);
    struct Sub* s = p->m510;
    if (s->b4 == 0) {
        p->m4f0 = 1.0f;
        unsigned char* r5 = (unsigned char*)p + 0x8bc;
        if (p->m508 <= 0) {
            func_00656B60(r5, 6);
            return;
        }
        if (p->m3a0 == p->m8e0) {
            func_00656B60(r5, 2);
            return;
        }
        p->m8f8 = func_00521040(p);
        func_00656B60(r5, 0);
        return;
    }
    float d;
    {
        float f = p->m3e0;
        float s1 = 0.02f;
        d = f - s1;
    }
    float lim = -0.2f;
    if (lim > d) d = lim;
    p->m3e0 = d;
    func_004FB0D8(p, &p->m3e0);
}
