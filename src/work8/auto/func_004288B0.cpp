typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

struct Inner {
    char pad[0xc0];
    f32 m0c0;
    char pad2[0xf4 - 0xc4];
    u8 mF4;
};
struct Outer {
    char pad[4];
    Inner* m4;
};

extern "C" void func_004288B0(Outer* p, f32 v) {
    Inner* o = p->m4;
    if (o) {
        Inner * t0 = o;
        bool ch = t0->m0c0 != v;
        t0->mF4 = o->mF4 | (ch << 2);
        if (ch) {
            o->m0c0 = v;
        }
    }
}
