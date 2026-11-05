typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;
typedef short s16;

struct E {
    char p0[0x14];
    f32 m14;
    char p18[4];
    f32 m1c;
    f32 m20;
    char p24[4];
    u8 m28;
    char p29[0x38 - 0x29];
};

struct Arr {
    char p0[8];
    u32 m8;
    E* mc;
    E* at(u32 i) {
        if (i < m8) return mc + i;
        return mc;
    }
};

struct Self {
    char p0[2];
    s16 m2;
    char p4[4];
    Arr* m8;
};

bool func_00532BA0(Self* self) {
    Arr* a = self->m8;
    if (a == 0) return true;
    s16 i = self->m2;
    if (i < 0) return true;
    E* e = a->at((u32)i);
    if (e->m28 != 0) return false;
    if (e->m1c >= 0.0f) {
        if (e->m14 == e->m20) return true;
        return false;
    }
    if (!(e->m14 > 0.0f)) return true;
    return false;
}
