// sead math types: 2D/4D vectors, 3x3/3x4 matrices, fixed-point angles, the sin/cos table sample
// and the sinCos/getRot helpers. One definition per game type for every matched source.
//
// Field and helper forms come from the matched sources; byte evidence is noted per member. Uncalled
// inline members generate no code, so the helpers are a superset. Types are spelled with plain C
// types (like vec3.h) so that a file's own typedefs cannot collide with a shared typedef.
//
// Free Vec3 operators (operator+, operator-, operator*) are NOT declared here: the game's
// 0x115C54/0x115C70/0x115D70 functions are exposed as the Vec3 members setAdd/setSub/setMul in
// vec3.h, and the 15 matched sources that want the operator spelling define inline wrappers in
// their own TU (e.g. src/work8/opus8/001B00E4.cpp); a non-inline declaration here would collide
// with those inline definitions. nn::math's MTX34 inverse at 0x11558C is hand-written VFP asm and
// likewise stays out.

#ifndef SEAD_MATH_H
#define SEAD_MATH_H

#include "vec3.h"

// sead::Vector2f (stand-in name Vec2). The plain 8-byte struct ({x, y}) is what 6 matched sources
// write; three more add a default ctor, a 2-arg ctor and set(). The y-then-x store order in set()
// is byte evidence from 001DE958 (`m9c.set(1.5f, 0.0f)` compiles to a y store followed by an x
// store).
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}
    void set(float x_, float y_) { y = y_; x = x_; }
};

// Alternate spelling of the same 2D vector used by two sources (0043D904, 0033CFB0).
typedef Vec2 Vec2f;

// 4-float vector. Every matched source writes it as a plain aggregate (7 as `{f32 x,y,z,w;}`,
// 2 as `{f32 x, y, z, w;}`, 2 with float); no helpers are needed by the matched functions.
struct Vec4 {
    float x, y, z, w;
};

// 3x3 matrix: 9 floats. getRot (0x1151D8) fills one from an Mtx34's rotation part. The sources
// name the member `e` (001151CC) or `v` (00124694), so both spellings alias the same storage.
struct Mtx33 {
    union {
        float m[9];
        float e[9];
        float v[9];
    };
};

// 3x4 matrix: 12 floats. The majority of sources spell it `m[3][4]` (6 sources + makeT user),
// four spell it as a flat array named `m`, one as `a[12]`, and the Matrix34 sources use `e`, `v`
// or `m`. A union keeps every spelling over the same 48 bytes; the flat array is reached as `a`
// (a source that indexes a flat `m` needs the rename m[idx] -> a[idx]).
struct Mtx34 {
    union {
        float m[3][4];
        float a[12];
        float e[12];
        float v[12];
        float data[12];
    };

    // Identity rotation + translation column (00202C20, byte-verified store order).
    void makeT(const Vec3& t) {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
        m[0][3] = t.x;  m[1][3] = t.y;  m[2][3] = t.z;
    }

    // Translation getter as two matched sources write it (002158D8, 00215F70): flat indices 3, 6, 9.
    void translation(Vec3* p) const { p->x = a[3]; p->y = a[6]; p->z = a[9]; }
    // The third source (00215AC8) writes the same helper with flat indices 3, 7, 11 and calls it;
    // the two forms produce different loads, so both are kept under distinct names and that file
    // gets the rename translation( -> translationRM(.
    void translationRM(Vec3* p) const { p->x = a[3]; p->y = a[7]; p->z = a[11]; }
};

// Alternate spellings of the same 12-float matrix in the matched sources (Matrix33/Matrix34 in
// 001151CC/001151EC/00124694/002FCAC0, Mtx in 003639D0/0038B25C/0039F998/0055693C).
typedef Mtx33 Matrix33;
typedef Mtx34 Matrix34;
typedef Mtx34 Mtx;

// Rotation part of a 3x4 matrix into a 3x3 one. 0x1151D8: vldmia 12 floats, three vstmia of 3
// floats each, translation column skipped. No matched source calls it yet (declaration only).
void getRot(Mtx33* out, const Mtx34* in);

// sinCos(f32* sin, f32* cos, u32 angle) at 0x115154: the high byte selects a SinCosSample in
// ro_006C3AB8 (16 bytes each), the low 24 bits interpolate by 1/2^24. 17 matched sources call it
// through their own local prototype named func_00115154.
void sinCos(float* s, float* c, unsigned int angle);

// Fixed-point angle in sead's 32-bit units. Matched sources write a default ctor (00202C20:
// `Angle m908;`), a converting ctor (001B00E4: `Angle(an - s->m3e8)`), add/sub helpers (0021BB4C:
// `m1350.add(...)`/`.sub(...)`) and a u32-typed variant (0038428C: `struct Angle{u32 v;...}`);
// the 32-bit value is the same storage, so one signed member covers all four forms.
struct Angle {
    int v;
    Angle() {}
    Angle(int n) : v(n) {}
    void add(int n) { v += n; }
    void sub(int n) { v -= n; }
};

// The same type under the spelling used by seven other matched sources (00206DB8, 00211574,
// 00202C20, ...).
typedef Angle AngleT;

// Interpolation entry read by sinCos and the inline sinIdx helpers: value + delta per quadrant.
// All 10 matched sources write this exact 16-byte struct.
struct SinCosSample {
    float sin_val, sin_delta, cos_val, cos_delta;
};

#endif
