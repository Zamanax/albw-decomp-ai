typedef unsigned int u32;
typedef unsigned char u8;

struct Pair { u32 a, b, c; };
struct Fl { float x, y, z; };
struct Obj {
    u32 m0;
    Pair* m4;
    Fl* m8;
    u8 m0c;
};

extern "C" u32 func_00392DBC(Obj* self) {
    if (self->m0c == 0) {
        return 1;
    }
    u32 v = self->m4->a;
    self->m4->c = v;
    self->m4->b = v;
    self->m8->y = self->m8->y * 0.5f;
    self->m8->y = self->m8->y - 0.002f;
    self->m8->x *= 0.75f;
    self->m8->z *= 0.75f;
    u8 c = self->m0c;
    self->m0c = c - 1;
    return 0;
}
