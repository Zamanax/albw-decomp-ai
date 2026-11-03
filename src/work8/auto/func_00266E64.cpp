typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Vec3 {
    f32 x, y, z;
};

struct StateMgr2 {
    u32 mCounter;
};

struct En {
    char p0[0x3d0];
    Vec3 m3d0;          // 0x3d0
    Vec3 m3dc;          // 0x3dc
    s32 m3e8;           // 0x3e8
    char p3ec[0x8c8 - 0x3ec];
    StateMgr2 mState;   // 0x8c8
    void f();
};

f32 func_004F898C();
void func_004F8964(f32* vy, bool clamp, f32 g);
Vec3* func_00520FC0(En* e);
void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);
inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r; func_00115C70(&r, a, b); return r; }
s32 func_0068C690(const Vec3& v);
f32 func_0058AC38(En* e);
f32 func_0058AA40(En* e);
void func_0051D2CC(s32* cur, f32 rate, s32 tgt);
void func_00660718(StateMgr2* sm, s32 s);

void En::f() {
    func_004F8964(&m3dc.y, true, func_004F898C());
    Vec3 d = *func_00520FC0(this) - m3d0;
    s32 ang = func_0068C690(d);
    func_0051D2CC(&m3e8, 0.05f, ang);
    if ((s32)mState.mCounter > 0x78) {
        if (func_0058AA40(this) == func_0058AC38(this)) func_00660718(&mState, 5);
    }
}
