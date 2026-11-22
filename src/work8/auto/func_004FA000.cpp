// One translation unit (data anchor 0x0070A570): the eight functions whose function-local statics
// fill the unit's .data from 0x70A570. armcc lays a unit's .data out as: explicitly initialised
// variables, then the function-local statics (guard, then the object when it is <= 8 bytes; larger
// objects go to .bss) of the file-scope functions in definition order, then those of member
// functions (by class, in declaration order), then the zero/dynamically initialised globals.
//   004FA000 guard +0x00 / colour +0x04    0058A7F4 guard +0x08 / word +0x0C
//   004F95A0 guard +0x10 / colour +0x14    0058A378 guard +0x18 (Vec3 in .bss 0x7368C8)
//   004FC994 guard +0x1C / colour +0x20    0058ADE0 guard +0x24 / colour +0x28
//   004F790C guard +0x2C (.bss 0x7368D4)   004F6F14 guard +0x30 (.bss 0x736940)
// then the unit's colours at +0x34/+0x38/+0x3C (initialised by the unit's static initializer
// 0x0059FF94, which also sets the Id64 at +0x40 and the pair at +0x48).
// armlink orders code by section name (i.<mangled name>), so these functions are not adjacent in
// the binary; the .data order is the source order.
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

#include "vec3.h"

// Colour as the model API takes it (r, g, b, a in memory order).
struct Color4u8 {
    u8 r, g, b, a;
    Color4u8(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};

// Colour stored alpha first (a, b, g, r in memory order).
struct ColorABGR {
    u8 a, b, g, r;
    ColorABGR() : a(0xFF), b(0), g(0), r(0) {}
    ColorABGR(u8 r_, u8 g_, u8 b_, u8 a_) : a(a_), b(b_), g(g_), r(r_) {}
    void set(const ColorABGR& o) { r = o.r; g = o.g; b = o.b; a = o.a; }
};

struct Mtx34 { f32 m[3][4]; };
extern "C" void func_001119F4(Mtx34* dst, const Mtx34* src);   // Matrix34 copy
extern const Vec3 bss_007A9254;    // zero vector
extern const Mtx34 bss_007A96F0;   // identity matrix

struct MdlRes { u16* data; s32 num; };
struct Model {
    u8 pad0[0x20];
    MdlRes* m20;
    u8 pad24[0x134 - 0x24];
    f32 m134;
    u8 pad138[0x164 - 0x138];
    u32 m164;
};
void func_004CF5DC(Model* m, s32 i, s32 k, const Color4u8* c);
const Color4u8* func_00584CA8(Model* m, s32 i, s32 k);

struct MdlEntry {
    Model* mdl;
    u8 flags;
    f32 f;
    MdlEntry();   // 0x004FD414
};

struct ModelList {
    MdlEntry e[7];
    u8 pad54[0xa8 - 0x54];
    u8 count;
};

ColorABGR data_0070A5A4(0xFF, 0xFF, 0xFF, 0xA0);
ColorABGR data_0070A5A8(0xFF, 0xFF, 0xFF, 0xA0);
ColorABGR data_0070A5AC(0x96, 0x46, 0x50, 0xFF);

// ---- 0x004FA000 ----
const ColorABGR* func_004FA000(s8 type) {
    static ColorABGR sColor;
    if (type) sColor.set(data_0070A5A8);
    else sColor.set(data_0070A5A4);
    return &sColor;
}

// ---- 0x0058A7F4 ----
struct Handle { u32 v; Handle() : v(0) {} };
struct Sub58A { u8 pad[0x2c]; Handle m2c; };
struct Obj58A {
    u8 pad0[0x430];
    Sub58A* m430;
    Sub58A* m434;
    u8 pad438[0x4b5 - 0x438];
    u8 m4b5;
};
Handle* func_0058A7F4(Obj58A* o) {
    if (!o->m4b5 && o->m430) return &o->m430->m2c;
    if (o->m434) return &o->m434->m2c;
    static Handle sNone;
    sNone.v = 0;
    return &sNone;
}

// ---- 0x004F95A0 ----
struct Enemy {
    u8 pad0[0x5a8];
    ModelList m5a8;
    u8 pad654[0x77c - 0x654];
    u8 m77c;
    u8 pad77d[0x824 - 0x77d];
    ColorABGR m824;
    u8 pad828[0x848 - 0x828];
    s8 m848;
    u8 pad849[0x851 - 0x849];
    u8 m851;
};
void func_004F95A0(Enemy* self, bool on) {
    const ColorABGR* c;
    self->m77c = on;
    if (on) {
        c = &self->m824;
    } else {
        static ColorABGR sColor;
        s8 t = self->m848;
        sColor = *func_004FA000(t);
        if (t == 0) sColor.a = self->m851;
        c = &sColor;
    }
    Color4u8 c0(c->r, c->g, c->b, c->a);
    Color4u8 c1(self->m824.r, self->m824.g, self->m824.b, self->m824.a);
    ModelList* l = &self->m5a8;
    for (u32 i = 0; i < l->count; i++) {
        MdlEntry* e = &l->e[i];
        Model* m = e->mdl;
        if (m) {
            for (s32 j = 0; j < m->m20->num; j++) {
                if (e->flags & 2) func_004CF5DC(m, j, 2, &c0);
                else func_004CF5DC(m, j, 2, &c1);
            }
        }
    }
}

// ---- 0x0058A378 ----
// The static's type has a user-declared default constructor that is defined (empty) only after this
// function: the front end then keeps the guard, and the back end inlines the empty body, which
// leaves the game's empty acquire/release pair.
struct Pos3 {
    f32 x, y, z;
    Pos3();
    Pos3& operator=(const Pos3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Obj58A3 { Pos3 pos; u8 padc[0x2c - 0xc]; f32 m2c; };
const Pos3& func_0058A378(Obj58A3* o) {
    static Pos3 sPos;
    sPos = o->pos;
    sPos.y = o->m2c;
    return sPos;
}
inline Pos3::Pos3() {}

// ---- 0x004FC994 ----
bool func_004FC994(ModelList* self, Model* m) {
    if (m == 0 || self->count == 0) return false;
    MdlEntry tmp[7];
    u8 n = self->count;
    for (u32 i = 0; i < n; i++) {
        tmp[i] = self->e[i];
        self->e[i].mdl = 0;
        self->e[i].flags = 0xb;
        self->e[i].f = 1.0f;
    }
    self->count = 0;
    bool found = false;
    for (u32 i = 0; i < n; i++) {
        MdlEntry* t = &tmp[i];
        Model* p = t->mdl;
        if (p == 0 || p == m) {
            found = true;
            continue;
        }
        u32 c = self->count;
        f32 f = t->f;
        if (c >= 7) continue;
        bool dup = false;
        for (u32 j = 0; j < c; j++) {
            if (self->e[j].mdl == p) { dup = true; break; }
        }
        if (dup) continue;
        if (f >= 0.0f) p->m134 = f;
        for (s32 k = 0; k < p->m20->num; k++) {
            u16* q = p->m20->data + k * 0xaa;
            if (q) *q |= 0x400;
        }
        self->e[self->count].mdl = p;
        self->e[self->count].flags = t->flags;
        self->e[self->count].f = f;
        self->count++;
    }
    if (found) {
        static Color4u8 sWhite(0xFF, 0xFF, 0xFF, 0xFF);
        m->m164 |= 0x4000;
        m->m164 &= ~0x80000;
        m->m164 |= 0x4000;
        m->m164 &= ~0x10000;
        for (s32 k = 0; k < m->m20->num; k++) func_004CF5DC(m, k, 2, &sWhite);
    }
    return found;
}

// ---- 0x0058ADE0 ----
const ColorABGR* func_0058ADE0(ModelList* self, s32 k) {
    static ColorABGR sColor(0x80, 0x80, 0x80, 0x80);
    for (u32 i = 0; i < self->count; i++) {
        Model* m = self->e[i].mdl;
        if (!m) continue;
        s32 j = 0;
        if (m->m20->num > 0) {
            const Color4u8* c = func_00584CA8(m, j, k);
            sColor.r = c->r;
            sColor.g = c->g;
            sColor.b = c->b;
            sColor.a = c->a;
            goto done;
        }
    }
    sColor.a = 0x80;
    sColor.b = 0x80;
    sColor.g = 0x80;
    sColor.r = 0x80;
done:
    return &sColor;
}

// ---- 0x004F790C / 0x004F6F14 ----
struct Pose {
    Vec3 t;
    Mtx34 r;
    Mtx34 s;
    Pose() : t(bss_007A9254) { func_001119F4(&r, &bss_007A96F0); func_001119F4(&s, &bss_007A96F0); }
};
void func_006824D4(void* mdl, const Vec3* scale, const Mtx34* rot, const Vec3* trans);
void func_00491E80(Mtx34* out, s32 a, s32 b, s32 c);

struct Placer {
    u8 pad0[0x10];
    Vec3 m10;
    Vec3 m1c;
    void* m28;
    void* m2c;
    void* m30;
    void* m34;
    u8 pad38[0x4c - 0x38];
    u8 m4c;
};
void func_004F790C(Placer* self, const Vec3* pos, const Vec3* scale) {
    if (!self->m2c) return;
    static Pose sPose;
    Vec3 t = *pos + self->m10;
    Vec3 s(self->m1c.x * scale->x, self->m1c.y * scale->y, self->m1c.z * scale->z);
    func_006824D4(self->m2c, &s, &sPose.r, &t);
}

void func_004F6F14(Placer* self, const Vec3* pos, const Vec3* scale, s32 a, s32 b) {
    if (!self->m30) return;
    self->m4c = 0;
    if (self->m34) {
        ((u32*)self->m34)[0] = 0;
        ((f32*)self->m34)[1] = -3.4028235e38f;
    }
    static Pose sPose;
    self->m10.x = 0.0f;
    self->m10.y = self->m1c.y * scale->y * 0.5f;
    self->m10.z = 0.0f;
    Vec3 t = *pos + self->m10;
    Mtx34 r;
    func_00491E80(&r, a, b, 0);
    Vec3 s(self->m1c.x * scale->x, self->m1c.y * scale->y, self->m1c.z * scale->z);
    func_006824D4(self->m30, &s, &r, &t);
}
