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
struct Vec3 { f32 x, y, z; };
struct Pos { u32 a; Vec3 pos; };
extern "C" void func_0052FDCC(void*, Vec3*);
extern "C" void func_0024100C(void*);
extern "C" void func_004ED9C8(void*);
extern "C" void func_001512B4(void*, void*);
struct Owner {
    u8 p0[0x40c]; Pos* m40c;
    u8 p1[0x4b8 - 0x410]; void* m4b8; void* m4bc;
    StateMgr mMgr;
    void* m4e4; void* m4e8;
    void func_00241300();
};
void Owner::func_00241300() {
    StateMgr* s = &mMgr; s->exec();
    {
    Vec3 v;
    func_0052FDCC(this, &v);
    v.y += 0.5f;
    v.z += -0.4f;
    Pos* p = m40c;
    p->pos.x = v.x;
    p->pos.y = v.y;
    p->pos.z = v.z;
    }
    func_0024100C(this);
    func_004ED9C8(m4e4);
    func_004ED9C8(m4e8);
    func_001512B4(m4b8, (u8*)this + 0x3d0);
}
