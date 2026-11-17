typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;

extern "C" void func_001B6C04(void*);
extern "C" void func_00231448(void*);
extern "C" void func_00462924(void*);

struct Elem {
    u8 pad0[0x1c];
    float f1c;
    float f20;
    u8 pad1[0x38 - 0x24];
};

struct Arr {
    u8 pad0[8];
    s32 count;
    Elem* data;
    Elem& at(u32 i) {
        if (i < (u32)count) return data[i];
        return data[0];
    }
};

struct S {
    u8 pad0[0x1c];
    Arr* m1c;
    u8 pad1[0x22 - 0x20];
    s16 m22;
    u8 pad2[0x80 - 0x24];
    u8 m80;
    u8 pad3[0x84 - 0x81];
    float m84;
    u8 pad4[0x90 - 0x88];
    u32 m90;
};

extern "C" void func_004626DC(S* p) {
    func_001B6C04(p);
    if (p->m84 > 0.0f) {
        Arr* a = p->m1c;
        s16 idx = p->m22;
        float q = a->at(idx).f20 / p->m84;
        a->at(idx).f1c = q;
    }
    func_00231448((u8*)p + 0x2c);
    p->m80 = 1;
    p->m90 = 0;
    func_00462924(p);
}
