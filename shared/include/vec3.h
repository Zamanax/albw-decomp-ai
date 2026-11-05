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


// Used by the inline length()/setLength(). Matches the declaration style of the matched sources
// (e.g. src/work8/opus8/004CA298.cpp).
extern "C" float sqrtf(float);

struct Vec3 {
    float x, y, z;

    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    // A source with a different store order in its local 3-arg ctor (x, z, y: 001D41D4) cannot
    // use this one; changing the order here breaks two of the 448 current users instead.
    // Difference of two vectors, used as an inline replacement for `a - b` at a call site
    // (001A5D24: `Vec3 diff(*func_00520FC0(s), s->m3d0)`). Written out of line by the game's
    // Vec3::setSub at 0x115C70.
    Vec3(const Vec3& a, const Vec3& b) { setSub(a, b); }

    void set(float a, float b, float c) { x = a; y = b; z = c; }
    void set(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    // A user-provided operator= would change all plain `a = b` copies (35 matched functions in
    // the current 444 users reject it), so the two sources that write one out keep their local
    // Vec3 (001FE514, 0028B008) instead.
    // A second copy helper: whole-struct assignment inside an inline body gives the split
    // `ldm {r2,r3}; ldr; str; strd` copy (001D4948, 001E4A5C, 002158D8), which neither the
    // memberwise set() above nor a plain `a = b` produces. Both forms exist in the game.
    void setCopy(const Vec3& o) { *this = o; }
    void setZero() { for (int i = 0; i < 3; ++i) (&x)[i] = 0.0f; }
    // The same "zero the vector" helper under the second spelling the sources use (001FE514,
    // 00215AC8 write `zero()`, 0028B008 and 29 users write `setZero()`); both bodies are the
    // source's own, and an uncalled inline member generates no code.
    void zero() { for (int i = 0; i < 3; ++i) (&x)[i] = 0.0f; }
    float squaredLength() const { return x * x + y * y + z * z; }
    // Declared only: 00217A0C supplies the out-of-line definition in its own TU
    // (`f32 Vec3::length()const{f32 sq=x*x+y*y+z*z;return sqrtf(sq);}`). An inline body here
    // would be a redefinition in that file. No matched source calls length() without defining it.
    float length() const;
    // Scales the vector to the given length and returns the previous length (004CA298). The
    // source calls the inline length() here; spelling its body out gives the same code without
    // forcing length() to be defined in this header.
    float setLength(float t) {
        const float len = sqrtf(x * x + y * y + z * z);
        if (len > 0.0f) { const float s = t / len; x *= s; y *= s; z *= s; }
        return len;
    }
    Vec3& setTo(const Vec3& v) { x = v.x; y = v.y; z = v.z; return *this; }

    void setAdd(const Vec3& a, const Vec3& b);            // 0x115C54
    void setSub(const Vec3& a, const Vec3& b);            // 0x115C70
    void setMul(const Vec3& a, float s);                    // 0x115D70
    void setDiv(const Vec3& a, float s);                    // 0x115D88
    void setScaleAdd(float s, const Vec3& a, const Vec3& b);  // 0x115DAC
    float normalize();                                      // 0x115DC8
    // Out-of-line members whose definitions live in the TUs that use them (001B00E4).
    Vec3& operator-=(const Vec3& o);
    void sub(const Vec3& o);

    Vec3& operator+=(const Vec3& o) { setAdd(*this, o); return *this; }
    float dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
};

#endif
