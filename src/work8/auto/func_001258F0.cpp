typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef float f32;


#include "vec3.h"

void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);
inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r; func_00115C70(&r, a, b); return r; }
s32 func_0068C690(const Vec3& v);
struct En;
Vec3* func_0051DAA4(En* e);
void func_0014FAFC(En* e, s32 ang, f32 rate);
struct Random;
u32 func_00111A64(Random* r);
inline u32 randU32(Random* r, u32 max) { return ((u64)func_00111A64(r) * max) >> 32; }
extern char* data_007124F0;

struct En {
    char p0[0x3d0];
    Vec3 m3d0;
    char p3dc[0x8e0 - 0x3dc];
    u32 m8e0;
    u32 m8e4;
    char p8e8[4];
    s32 m8ec;
    void f();
};

void En::f() {
    s32 ang;
    Vec3* p = func_0051DAA4(this);
    if (p) {
        Vec3 d = *p - m3d0;
        ang = func_0068C690(d);
    } else {
        ang = func_00111A64((Random*)(data_007124F0 + 0x660));
    }
    m8e4 = ang;
    func_0014FAFC(this, ang, 0.06f);
    m8ec = randU32((Random*)(data_007124F0 + 0x660), 60) + 120;
}
