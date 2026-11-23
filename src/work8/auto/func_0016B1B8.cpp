typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

extern "C" {
void func_003CBCDC(void* buf);
void* func_00110D44(void* dst, const void* src, u32 n);
}

struct Cmp {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
};
struct Node { virtual void s0(); };
struct Elem56 {
    u32 a0;
    u8 p4[4];
    f32 f8;
    f32 fc;
    f32 f10;
    u8 b14, b15, b16, b17;
    u8 rest[0x20];
};
struct Obj {
    char p0[0x10];
    void* m10;
    char p1[0x90 - 0x14];
    u32 m90;
    char p2[0x98 - 0x94];
    Node** m98;
    Node* m9c;
    char p3[0x284 - 0xa0];
    Elem56 elems[0x33];
    char p4[0xf74 - (0x284 + 0x33 * 0x38)];
    u32 f74;
    u32 f78;
    char p5[0xf88 - 0xf7c];
    f32 f88;
    Cmp* f8c[2];
    u8 f94;
    char p6[0xfa8 - 0xf95];
    u8 fa8;
    u8 fa9;
    u8 faa;
};

extern "C" void func_0016B1B8(Obj* self)
{
    u8 buf[0x1b4];
    self->f78 = 0;
    func_003CBCDC(buf);
    f32 z = 0.0f;
    for (s32 i = 0; i < 0x30; ++i) {
        u16 k = (u16)i;
        Obj * t0 = self;
        u8* d = 632 * (u32)k + (u8*)t0->m10;
        func_00110D44(d + 4, buf, 0x1b0);
        Elem56* e = self->elems;
        if ((u32)i < 0x33) e += i;
        e->a0 = 0;
        e->b14 = 0;
        e->b15 = 1;
        e->b16 = 1;
        e->b17 = 1;
        e->f8 = z;
        e->fc = z;
        e->f10 = z;
    }
    self->fa8 = 1;
    self->f74 = 0;
    for (s32 j = 0; j < (s32)self->m90; ++j) {
        Node* n = self->m98[j];
        n->s0();
        *(Node**)n = self->m9c;
        self->m9c = n;
    }
    self->m90 = 0;
    u8 t = (u8)(1 - self->f94);
    self->f94 = t;
    self->f8c[t]->v10();
    self->fa8 = 0;
    f32 c = 0.85f;
    self->faa = self->fa9 = 0;
    self->f88 = c;
}
