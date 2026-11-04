// func_005DE4A8 - static initializer (__sti__).
// Writes: -1 (s64) at 0x709CD0, 0 (s64) at 0x709CD8, FLT_MAX at 0x709CC8 and 0x709CCC.
typedef float f32;
typedef long long s64;

struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };

// 16-byte object whose s64 sits at +8: the built-in aggregate initializer is what makes
// armcc emit `strd r0, r1, [r2, #8]` with the object's base as the pool constant.
struct Big { char pad[8]; s64 v; };

struct C_t { f32 x, y; C_t() {} };

extern C_t C;

// runs last, resets the float pair
struct Setter { s64 pad; Setter() { C.y = 3.40282347e38f; C.x = 3.40282347e38f; } };

Big A = { {0}, Id64().v };
C_t C;
// this global is 16-byte aligned, so C ends up 0x10 bytes before it (armcc derives &C as
// `sub r0, r0, #0x10` from the constant it materializes for B)
__align(16) Pair B;
Setter S;
