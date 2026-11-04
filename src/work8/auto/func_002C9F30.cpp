typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);
struct StateMgr {
    u32 mCount; s8 mCur; s8 mNext; u8 mNum; u8 pad7; u32 mNames[2]; void* mTimeline;
    Base* mOwner; PMF* mEnter; PMF* mExec; PMF* mExit;
    void exec() {
        (mOwner->*mExec[mCur])();
        u32 c = ++mCount;
        if (mTimeline) func_00352210(mTimeline, 1, (f32)c);
    }
};

#include "vec3.h"

struct RecU { u32 h; f32 x, y, z; };
struct Owner {
    u8 pad[0x40c]; RecU* m40c; u8 p410[0x4b8 - 0x410];
    StateMgr mMgr; void* m4dc; void* m4e0;
    void func_002C9F30();
};
extern "C" void func_0052FDCC(Owner*, Vec3*);
extern "C" void func_002C9C78(Owner*);
extern "C" void func_004ED9C8(void*);
void Owner::func_002C9F30() {
    StateMgr* s = &mMgr; s->exec();
    {
        Vec3 tmp;
        func_0052FDCC(this, &tmp);
        tmp.y += 0.5f;
        RecU* d = m40c;
        d->x = tmp.x; d->y = tmp.y; d->z = tmp.z;
    }
    func_002C9C78(this);
    func_004ED9C8(m4dc);
    func_004ED9C8(m4e0);
}
