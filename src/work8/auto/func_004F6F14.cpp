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

struct Mtx34;
void func_00491E80(Mtx34* out, s32 rx, s32 ry, s32 rz);   // rotation matrix from three angles
struct Mtx34 {
    f32 m[3][4];
    Mtx34() {}
    // The rotation constructor: through it, the call's arguments are set up in order (r0 first) and
    // the angle parameters keep the game's registers (004F6F14); a direct call does neither.
    Mtx34(s32 rx, s32 ry, s32 rz) { func_00491E80(this, rx, ry, rz); }
};
extern "C" void func_001119F4(Mtx34* dst, const Mtx34* src);   // Matrix34 copy
extern const Vec3 bss_007A9254;    // zero vector
extern const Mtx34 bss_007A96F0;   // identity matrix

// The model's flag word. set/reset go through change(): the if is resolved after armcc combines
// constants, so each call keeps its own orr/bic (004FC994), as in shared/include/flags.h.
struct ModelFlags {
    u32 v;
    void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u32 m) { change(m, true); }
    void reset(u32 m) { change(m, false); }
};

// A model's materials: 0x154 bytes each, a flag halfword first.
struct Material { u16 flags; u8 pad2[0x154 - 2]; };
struct MdlRes {
    Material* mats;
    s32 num;
    Material* get(s32 k) const { return mats + k; }
};
struct Model {
    u8 pad0[0x20];
    MdlRes* m20;
    u8 pad24[0x134 - 0x24];
    f32 m134;
    u8 pad138[0x164 - 0x138];
    ModelFlags m164;
};
void func_004CF5DC(Model* m, s32 i, s32 k, const Color4u8* c);
const Color4u8* func_00584CA8(Model* m, s32 i, s32 k);

// An entry's flag byte (0xB after reset and in the constructor 0x004FD414). set() is defined out of
// line below, so it is inlined late: the 0xB is materialised inside 004FC994's reset loop instead of
// being hoisted out of it.
struct EntFlags {
    u8 v;
    void set(u8 x);
};

struct MdlEntry {
    Model* mdl;
    EntFlags flags;
    f32 f;
    MdlEntry();   // 0x004FD414
};
void EntFlags::set(u8 x) { v = x; }

struct ModelList {
    MdlEntry e[7];
    u8 pad54[0xa8 - 0x54];
    u8 count;
    // Appends a model unless the list is full or already holds it (004FC994). A member: its early
    // returns leave the duplicate search straight to the caller's next iteration, and armcc then
    // unrolls that search by two like the game.
    bool add(Model* p, const MdlEntry& t) {
        f32 f = t.f;
        u32 c = count;
        if (c >= 7) return false;
        for (u32 j = 0; j < c; j++) {
            if (e[j].mdl == p) return false;
        }
        if (f >= 0.0f) p->m134 = f;
        for (s32 k = 0; k < p->m20->num; k++) {
            Material* mt = p->m20->get(k);
            if (mt) mt->flags |= 0x400;
        }
        e[count].mdl = p;
        e[count].flags = t.flags;
        e[count].f = f;
        count++;
        return true;
    }
    // Material colour slot 2 of every model: c0 where the entry's flag 2 is set, c1 elsewhere
    // (004F95A0). Inlined late: `this` stays in a register for the first count load as well.
    void setMatColor(const ColorABGR& a, const ColorABGR& b) {
        Color4u8 c0(a.r, a.g, a.b, a.a);
        Color4u8 c1(b.r, b.g, b.b, b.a);
        for (u32 i = 0; i < count; i++) {
            MdlEntry* p = &e[i];
            Model* m = p->mdl;
            if (m) {
                for (s32 j = 0; j < m->m20->num; j++) {
                    if (p->flags.v & 2) func_004CF5DC(m, j, 2, &c0);
                    else func_004CF5DC(m, j, 2, &c1);
                }
            }
        }
    }
};

ColorABGR data_0070A5A4(0xFF, 0xFF, 0xFF, 0xA0);
ColorABGR data_0070A5A8(0xFF, 0xFF, 0xFF, 0xA0);
ColorABGR data_0070A5AC(0x96, 0x46, 0x50, 0xFF);

// ---- 0x004FA000 ----
// Not inlined into 004F95A0 in the game: the unit's other callers (004F5BD8 twice, 004FD464) are not
// in this file, and with a single call site armcc -O3 inlines it. noinline stands in for them.
__declspec(noinline) const ColorABGR* func_004FA000(s8 type) {
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
    const ColorABGR& base = self->m824;
    self->m77c = on;
    const ColorABGR* c;
    if (on) {
        c = &base;
    } else {
        static ColorABGR sColor;
        // The type is read through an alias (found by tools/mutate.py): with self->m848, c0's
        // green and blue bytes swap registers (r1/r2). The alias only moves the allocation.
        const Enemy* e = self;
        s8 t = e->m848;
        sColor = *func_004FA000(t);
        ColorABGR* p = &sColor;
        if (t == 0) p->a = self->m851;
        c = p;
    }
    self->m5a8.setMatColor(*c, base);
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
        MdlEntry& d = self->e[i];
        tmp[i] = d;
        d.mdl = 0;
        d.flags.set(0xb);
        d.f = 1.0f;
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
        self->add(p, *t);
    }
    if (found) {
        static Color4u8 sWhite(0xFF, 0xFF, 0xFF, 0xFF);
        m->m164.set(0x4000);
        m->m164.reset(0x80000);
        m->m164.set(0x4000);
        m->m164.reset(0x10000);
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

// Component-wise product. The result is built through Vec3::set() on a local: written as a
// constructor call or as three member stores, the scale vector's loads and the result's registers
// come out in a different order (004F790C, 004F6F14).
inline Vec3 mulElem(const Vec3& a, const Vec3& b) {
    Vec3 r;
    r.set(a.x * b.x, a.y * b.y, a.z * b.z);
    return r;
}

// The pair 004F6F14 resets: an id and a running maximum. Through a member, the pointer is loaded
// once; written as two stores through self->m34, the second store reloads it.
struct MaxRec {
    u32 id;
    f32 val;
    void reset() { id = 0; val = -3.4028235e38f; }
};

struct Placer {
    u8 pad0[0x10];
    Vec3 m10;
    Vec3 m1c;
    void* m28;
    void* m2c;
    void* m30;
    MaxRec* m34;
    u8 pad38[0x4c - 0x38];
    u8 m4c;
};
void func_004F790C(Placer* self, const Vec3* pos, const Vec3* scale) {
    if (!self->m2c) return;
    static Pose sPose;
    Vec3 t = *pos + self->m10;
    Vec3 s = mulElem(self->m1c, *scale);
    func_006824D4(self->m2c, &s, &sPose.r, &t);
}

void func_004F6F14(Placer* self, const Vec3* pos, const Vec3* scale, s32 rx, s32 ry) {
    if (!self->m30) return;
    self->m4c = 0;
    if (self->m34) self->m34->reset();
    static Pose sPose;
    self->m10 = Vec3(0.0f, self->m1c.y * scale->y * 0.5f, 0.0f);
    Vec3 t = *pos + self->m10;
    Vec3 s = mulElem(self->m1c, *scale);
    Mtx34 r(rx, ry, 0);
    func_006824D4(self->m30, &s, &r, &t);
}
