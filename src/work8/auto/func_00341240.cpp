typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

struct Vec3 { f32 x, y, z; };
extern "C" void func_00115C54(Vec3* out, const Vec3* a, const Vec3* b);

struct Inner {
    u8 p0[0x3d0];
    Vec3 m3d0;
};

struct Sub {
    u8 p0[0x104];
    Vec3 m104;
};

struct Outer {
    u8 p0[0x24];
    Inner* m24;
    u8 p1[0x400 - 0x28];
    Sub m400;
};

void func_00341240(Outer* self) {
    Sub* s = &self->m400;
    Vec3 a;
    Inner * t2 = self->m24;
    Inner* p = t2;
    Vec3* t1 = &a;
    t1->x = 0.0f;
    t1->y = 0.5f;
    t1->z = 0.0f;
    Vec3* d = &s->m104;
    Vec3 r;
    func_00115C54(&r, &p->m3d0, t1);
    *d = r;
}
