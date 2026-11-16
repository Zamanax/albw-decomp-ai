typedef unsigned char u8;

struct Obj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(u8* p);
    virtual void v6(u8* dst, u8* src, u8 c);
    u8 f4;
    bool f5;
    u8 pad6[2];
    u8 x8[0x40];
    u8 x48[0x40];
    u8 b88;
};

u8* func_0057D5C4(Obj* self) {
    Obj * t0 = self;
    if (0 != t0->f4) {
        t0->v5(t0->x8);
        t0->f4 = 0;
        t0->f5 = 1;
    }
    u8 go = t0->f5;
    if (go != 0) {
        Obj* o = self;
        Obj * t1 = self;
        o->v6(t1->x48, t1->x8, self->b88);
        self->f5 = 0;
    }
    return self->x48;
}
