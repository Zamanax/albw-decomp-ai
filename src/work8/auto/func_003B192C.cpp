typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

struct P {
    char p0[8];
    f32 m8;
    char pc[4];
    f32 m10;
    f32 m14;
    char p18[4];
    u8 m1c;
};

struct B {
    char p0[0x14];
    P* m14;
};

struct A {
    char p0[0x8dc];
    B* m8dc;
};

struct Self;
typedef void (*VFn)(Self*, u32, u32);

struct Self {
    char p0[0x48];
    A* m48;
};

void func_003B192C(Self* self) {
    P* p = self->m48->m8dc->m14;
    if (p->m1c != 0) return;
    bool go;
    if (p->m10 >= 0.0f) {
        go = (p->m8 == p->m14);
    } else {
        go = !(p->m8 > 0.0f);
    }
    if (go) {
        VFn f = ((VFn*)(*(void**)self))[0x138 / 4];
        f(self, 1, 1);
    }
}
