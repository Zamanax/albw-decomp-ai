typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef float f32;

struct Vec3 { f32 x, y, z; };
struct EffChild { char p0[4]; s32 m4; char p8[4]; u32 mc; char p10[0x280 - 0x10]; u8 m280; };
struct Eff {
    char p0[0x1c];
    u32 m1c;
    EffChild* m20;
    u32 m24;
    char p28[0x3c - 0x28];
    u32 m3c;
    bool childAlive() const { return m20 && m24 == m20->mc && m20->m4 > 0; }
    bool isPlaying() const {
        if (m3c & 4) return true;
        if (m3c & 0x40) return true;
        return childAlive();
    }
};
struct EffHandle {
    Eff* p;
    u32 id;
    bool isValid() const { return p && p->m1c == id; }
};
struct Ent48 { char p0[8]; f32 x; char p1[0xc]; f32 y; char p2[0xc]; f32 z; char p3[4]; };
struct Arr { char p0[0x14]; Ent48* m14; };
struct Mid { char p0[0x24]; Arr* m24; };
struct Obj4 {
    char p0[0x8d4];
    Mid* m8d4;
    char p1[0x8e8 - 0x8d8];
    u32 m8e8;
    char p2[0x900 - 0x8ec];
    f32 m900;
};
extern void* data_0070B960;
f32 func_0051E8AC(void* o, const Vec3* pos, f32 a, f32 b);

struct Sub8c0 { char p0[0x40]; f32 m40; };
struct En208 {
    char p0[4];
    Obj4* m4;
    char p8[0x1c4 - 8];
    EffHandle m1c4;
    void f();
};

void En208::f() {
    if (m1c4.isValid() && m1c4.p->isPlaying()) {
        Ent48* e = &m4->m8d4->m24->m14[m4->m8e8];
        Vec3 pos = { e->x, e->y, e->z };
        f32 r = func_0051E8AC(data_0070B960, &pos, 1.0f, 0.5f);
        Sub8c0* s = (Sub8c0*)((char*)m4 + 0x8c0);
        s->m40 = r;
    }
}
