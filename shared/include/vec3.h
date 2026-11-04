// Vec3: the game's 3-float vector (sead::Vector3f in the original; stand-in name).
//
// One definition for every matched source (tools/headermigrate.py measures how many independently
// matched functions accept it unchanged). Uncalled inline members generate no code, so members are
// a superset; where matched sources disagree on a member's form, the majority form is used and the
// disagreement is recorded in docs/LESSONS.md ("Shared headers").
//
// Out-of-line members are real game functions; their addresses are noted.

#ifndef VEC3_H
#define VEC3_H

#include "albw_types.h"

struct Vec3 {
    f32 x, y, z;

    Vec3() {}
    Vec3(f32 a, f32 b, f32 c) : x(a), y(b), z(c) {}

    void set(f32 a, f32 b, f32 c) { x = a; y = b; z = c; }
    void set(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    // A second copy helper: whole-struct assignment inside an inline body gives the split
    // `ldm {r2,r3}; ldr; str; strd` copy (001D4948, 001E4A5C, 002158D8), which neither the
    // memberwise set() above nor a plain `a = b` produces. Both forms exist in the game.
    void setCopy(const Vec3& o) { *this = o; }
    void setZero() { for (s32 i = 0; i < 3; ++i) (&x)[i] = 0.0f; }

    void setAdd(const Vec3& a, const Vec3& b);            // 0x115C54
    void setSub(const Vec3& a, const Vec3& b);            // 0x115C70
    void setMul(const Vec3& a, f32 s);                    // 0x115D70
    void setDiv(const Vec3& a, f32 s);                    // 0x115D88
    void setScaleAdd(f32 s, const Vec3& a, const Vec3& b);  // 0x115DAC
    f32 normalize();                                      // 0x115DC8

    Vec3& operator+=(const Vec3& o) { setAdd(*this, o); return *this; }
    f32 dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
};

#endif
