typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

extern "C" void func_00115154(f32 *sin, f32 *cos, u32 angle);

struct Pair {
    f32 y, z;
    Pair(f32 a, f32 b) : y(a), z(b) {}
};

// first basis vector of the frame: (sin, 0, cos)
struct First {
    f32 x, y;
    u32 cosBits;
};

// second basis vector of the frame: (cos, 0, -sin)
struct Second {
    u32 cosBits;
    Pair yz;

    void init(u32 bits, f32 sn) {
        cosBits = bits;
        yz = Pair(0.0f, -sn);
    }
};

struct S {
    u8 pad374[0x374];
    First first;
    Second second;
};

extern "C" void func_0014E4B0(S *p, u32 angle) {
    f32 sine, cosine;
    func_00115154(&sine, &cosine, angle);
    u32 bits = *(const u32 *)&cosine;
    p->first.x = sine;
    p->first.cosBits = bits;
    p->first.y = 0.0f;
    p->second.init(bits, sine);
}
