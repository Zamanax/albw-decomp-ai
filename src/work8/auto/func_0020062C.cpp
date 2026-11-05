typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef unsigned long long u64;


#include "sead_string.h"
namespace sead {

}


#include "vec3.h"



#include "timer.h"


struct StateMgr { void changeState(int s); };

void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);  // Vec3::setSub (out-of-line)
inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r; func_00115C70(&r, a, b); return r; }
s32 func_0068C690(const Vec3& v);   // angleFromVec
struct Obj70FB60 { char pad[0x1c]; Vec3* m1c; };
extern Obj70FB60* data_0070FB60;

struct Ang { s32 v; Ang() {} Ang(s32 x) : v(x) {} };
void func_0051D27C(Ang* ang, s32 target, s32 step);
struct En;
s32 func_00588BE4(En* e);   // getActorId
void func_0014FAFC(En* e, s32 ang, f32 rate);
void func_001507D8(En* e, const sead::SafeString& name, s32 v);  // actor playSE2
extern const s32 ro_006938F0;
extern const s32 ro_006938E4;
extern const s32 ro_006938EC;

struct En {
    char p0[0x3a4];
    u32 m3a4;           // 0x3a4
    u32 p3a8;
    f32 m3ac;           // 0x3ac
    char p3b0[0x3d0 - 0x3b0];
    Vec3 m3d0;          // 0x3d0
    Vec3 m3dc;          // 0x3dc
    u32 m3e8;           // 0x3e8
    char p3ec[0x420 - 0x3ec];
    char p420[0x4e4 - 0x420];
    Vec3 m4e4;          // 0x4e4
    char p4f0[0x800 - 0x4f0];
    char p800[0x8bc - 0x800];
    Timer m8bc;         // 0x8bc
    Timer m8c8;         // 0x8c8
    Ang m8d4;           // 0x8d4
    Ang m8d8;           // 0x8d8
    StateMgr mState;    // 0x8dc
    u8 m8dd[3];
    u8 m8e0;            // 0x8e0
    u8 m8e1;            // 0x8e1
    char p8e2[0x93c - 0x8e2];
    s8 m93c;            // 0x93c
    u8 m93d;            // 0x93d
    void f();
};
void En::f() {
    if (func_00588BE4(this) == ro_006938F0 && !m93c) {
        if (data_0070FB60) {
            Vec3 d = *data_0070FB60->m1c - m3d0;
            m8d4 = Ang(func_0068C690(d));
        }
        func_0051D27C(&m8d8, m8d4.v, 0xb60b60);
        { Ang a = m8d8; func_0014FAFC(this, a.v, 0.01f); }
        *(Ang*)&m3e8 = m8d8;
    }
    if (!m8c8.step()) mState.changeState(5);
    if (func_00588BE4(this) == ro_006938F0) {
        func_001507D8(this, sead::SafeString("SE_Gigabari_ELEC"), 0);
    } else if (func_00588BE4(this) == ro_006938E4 || func_00588BE4(this) == ro_006938EC) {
        func_001507D8(this, sead::SafeString("SE_Bari_ELEC"), 0);
    } else {
        func_001507D8(this, sead::SafeString("SE_Biri_ELEC"), 0);
    }
}
