typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

struct Obj1 {
    void* vt;
    u8 pad[0x2c];
    u8 f30;
    u8 f31;
    u32 f34;
};

extern "C" void func_003F8674(Obj1*, u32, u32, u32, f32, f32);

Obj1* func_003F99B8(Obj1* self, unsigned a, int b, int c, f32 x, f32 y) {
    self->vt = (void*)0x6efe88;
    Obj1 * t2 = self;
    t2->f30 = 0;
    Obj1 * t0 = t2;
    t0->f34 = t0->f31 = 0;
    func_003F8674(t2, a, b, c, x, y);
    return self;
}
