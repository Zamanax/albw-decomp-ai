typedef unsigned char u8; typedef unsigned int u32; typedef int s32; typedef float f32;
struct Vec3 { f32 x, y, z; };
struct AngleT { s32 v; AngleT(s32 n) : v(n) {} };
extern "C" void* data_0070FB60;
extern "C" Vec3* func_00520FC0(void* self);
extern "C" void func_00115C70(Vec3* o, const Vec3* a, const Vec3* b);
extern "C" s32 func_004905E0(f32);
extern "C" u32 func_0058E2B8(const AngleT& a);
inline s32 atan2Idx(f32 y, f32 x) {
    if (x == 0.0f && y == 0.0f) return 0;
    if (x >= 0.0f) {
        if (y >= 0.0f) {
            if (x >= y) return func_004905E0(y / x);
            else return 0x40000000 - func_004905E0(x / y);
        } else {
            if (x >= -y) return -func_004905E0(-y / x);
            else return 0xc0000000 + func_004905E0(x / -y);
        }
    } else {
        if (y >= 0.0f) {
            if (-x >= y) return 0x80000000 - func_004905E0(y / -x);
            else return 0x40000000 + func_004905E0(-x / y);
        } else {
            if (x <= y) return 0x80000000 + func_004905E0(y / x);
            else return 0xc0000000 - func_004905E0(x / y);
        }
    }
}
struct Obj { char p0[0x3d0]; Vec3 m3d0; char p3dc[0x3e8-0x3dc]; s32 m3e8; char p3ec[0x5fc-0x3ec]; s32 m5fc; };
extern "C" s32 func_0054C998(s32 a, s32 b);
extern "C" bool func_0052EBA0(Obj* o, const Vec3& p) {
    f32 dy, dz;
    {
        Vec3 d;
        func_00115C70(&d, &p, &o->m3d0);
        dy = d.x;
        dz = d.z;
    }
    s32 t = func_0054C998(o->m5fc, o->m3e8);
    s32 angle = atan2Idx(dy, dz);
    f32 r;
    {
        AngleT diff(t - angle);
        r = (f32)func_0058E2B8(diff) * 4.656612873e-10f;
    }
    return r < 0.3f;
}
