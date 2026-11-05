// sead math types: 2D/4D vectors, 3x3/3x4 matrices, angles, the sin/cos table sample and the
// sinCos helper. One definition per game type for every matched source.
//
// Field and helper forms come from matched sources; byte evidence is noted per member. Uncalled
// inline members generate no code, so the helpers are a superset. Types are spelled with plain C
// types (like vec3.h) so that a file's own typedefs cannot collide with a shared typedef.

#ifndef SEAD_MATH_H
#define SEAD_MATH_H

#include "vec3.h"

// sead::Vector2f (stand-in name Vec2). Matched with a default ctor + 2-arg ctor (001DE958,
// 00554E8C, 005E6138) and with the y-then-x store order of set() (001DE958: `m9c.set(1.5f, 0.0f)`
// is compiled as a y store followed by an x store).
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}
    void set(float x_, float y_) { y = y_; x = x_; }
};

// 4-float vector, no helpers needed by the matched sources.
struct Vec4 {
    float x, y, z, w;
};

// 3x3 matrix: the rotation part extracted by getRot (0x1151D8 stores 9 floats).
struct Mtx33 {
    float m[9];
};

// 3x4 matrix. m is row-major 3x4 (m[row][col]); a is the same 48 bytes as 12 floats, because the
// matched sources use both spellings (00202C20 writes m[r][c]; 002158D8/00215F70 read the
// translation column through a flat f32[12]).
struct Mtx34 {
    union {
        float m[3][4];
        float a[12];
    };

    // Identity rotation + translation (00202C20, byte-verified store order).
    void makeT(const Vec3& t) {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
        m[0][3] = t.x;  m[1][3] = t.y;  m[2][3] = t.z;
    }

    // Translation getter as the matched sources write it (002158D8, 00215F70): flat indices
    // 3,6,9 of the 12 floats. 00215AC8 spells the same helper with 3,7,11 but never calls it,
    // so only this byte-verified form is kept.
    void translation(Vec3* p) const { p->x = a[3]; p->y = a[6]; p->z = a[9]; }
};

// Rotation part of a 3x4 matrix into a 3x3 one (0x1151D8: vldmia 12 floats, three vstmia of 3
// floats each, translation column skipped). Not matched yet (hand-written asm shape).
void getRot(Mtx33* out, const Mtx34* in);

// sinCos(f32* sin, f32* cos, u32 angle) at 0x115154: high byte selects a SinCosSample in
// ro_006C3AB8 (16 bytes each), the low 24 bits interpolate by 1/2^24. Matched sources declare
// this prototype locally (0021BB4C, 0021A59C, ...).
void sinCos(float* s, float* c, unsigned int angle);

// Fixed-point angle in sead's 32-bit units. Matched sources write it with a default ctor
// (00202C20: `Angle m908;`), a converting ctor (001B00E4: `Angle(an - s->m3e8)`) and add/sub
// helpers (0021BB4C: `m1350.add(...)`/`.sub(...)`).
struct Angle {
    int v;
    Angle() {}
    Angle(int n) : v(n) {}
    void add(int n) { v += n; }
    void sub(int n) { v -= n; }
};

// The same type under the spelling used by the AngleT sources (00206DB8, 00211574, ...).
typedef Angle AngleT;

// Interpolation entry read by sinCos and the inline sinIdx helpers: value + delta per quadrant.
struct SinCosSample {
    float sin_val, sin_delta, cos_val, cos_delta;
};

#endif
