typedef unsigned int u32; typedef int s32; typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef float f32;

#include "vec3.h"

struct En1AA;
struct Timeline { void func_00352210(bool b, f32 frame); };
struct StateMgr {
    typedef void (En1AA::*Func)();
    u32 mCounter; s8 mCur; s8 mNext; u8 mNum; char pad7[0x10 - 7];
    Timeline* mTimeline; En1AA* mOwner; Func* mEnter; Func* mExec; Func* mExit;
    void func_0065A6FC(int s);
    void execute() { (mOwner->*mExec[mCur])(); ++mCounter; if (mTimeline) mTimeline->func_00352210(true, (f32)mCounter); }
};
f32 func_004F898C();
void func_004F8964(f32* v, bool clamp, f32 g);
void func_004FB0D8(En1AA* e, f32* vy);
bool func_004F70A8(En1AA* e);
bool func_004F8998(En1AA* e, s32 a, s32 b);
void func_004F48F0(En1AA* e);
void func_004F5588(En1AA* e);
void func_004F5BD8(En1AA* e, s32 a, s32 b);
void func_004F9554(void* p, s32 a, s32 b, s32 c);
struct En1AA {
    char p0[0x3dc];
    Vec3 m3dc;
    char p3e8[0x430 - 0x3e8];
    void* m430; void* m434;
    char p438[0x8bc - 0x438];
    StateMgr mState;
    char p8e0[0x8ff - 0x8e0];
    u8 m8ff;
    char p900[0x94c - 0x900];
    u16 m94c; u8 m94e; u8 m94f;
    void f();
};
void En1AA::f() {
    m94e = 0;
    if (m94c != 0) m94c--;
    if (!func_004F70A8(this)) return;
    s8 st = mState.mCur;
    if (st != 4 && st != 5 && st != 3) {
        if (func_004F8998(this, 0, 0)) mState.func_0065A6FC(4);
    }
    mState.execute();
    func_004F8964(&m3dc.y, true, func_004F898C());
    func_004FB0D8(this, &m3dc.y);
    func_004F48F0(this);
    func_004F5588(this);
    func_004F5BD8(this, 0, 0);
    m94f = 0;
    func_004F9554(m430, 0, 0, 1);
    func_004F9554(m434, 0, 0, 1);
}
