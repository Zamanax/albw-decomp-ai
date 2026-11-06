typedef unsigned int u32;
typedef int s32;
typedef float f32;

#include "vec3.h"

extern void* data_00708998;
Vec3* func_00588F14(void* p);
Vec3* func_00588F08(void* p);
void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);
inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r; func_00115C70(&r, a, b); return r; }
s32 func_0068C690(const Vec3& v);
void func_0051D2CC(s32* cur, f32 rate, s32 tgt);
void func_004F68AC(char* self, u32 a1);

void func_001257AC(char* a0, u32 a1)
{
    Vec3 d = *func_00588F14(data_00708998) - *func_00588F08(data_00708998);
    s32 ang = func_0068C690(d);
    func_0051D2CC((s32*)(a0 + 0x3e8), 0.4f, ang);
    func_004F68AC(a0, a1);
}
