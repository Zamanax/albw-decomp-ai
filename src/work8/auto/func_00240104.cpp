typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);
extern "C" void func_0014E2A0(void*, u32, void*, u32, u32, u32);
extern "C" void func_002401B4(void*);
struct StateMgr {
    u32 mCount; s8 mCur; s8 mNext; u8 mNum; u8 pad7; u32 mNames[2]; void* mTimeline;
    Base* mOwner; PMF* mEnter; PMF* mExec; PMF* mExit;
    void exec() {
        (mOwner->*mExec[mCur])();
        u32 c = ++mCount;
        if (mTimeline) func_00352210(mTimeline, 1, (f32)c);
    }
};
struct Owner { u8 pad[0x40c]; StateMgr mMgr; u8 pad2[0x434 - 0x430]; u32 mF434; u8 pad3[0x49c - 0x438]; void func_00240104(); };
void Owner::func_00240104() {
    mMgr.exec();
    func_0014E2A0(this, mF434, (u8*)this + 0x49c, 0x4000, 0, 0);
    func_002401B4(this);
}
