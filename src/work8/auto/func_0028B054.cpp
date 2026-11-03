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
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
struct Owner {
    u8 pad0[0x2d7]; u8 m2d7;
    u8 pad1[0x478 - 0x2d8]; void* m478;
    u8 pad2[0x4f4 - 0x47c]; StateMgr mMgr;
    u8 pad3[0x580 - 0x518]; void* m580;
    u8 pad4[0x5d4 - 0x584]; u8 m5d4;
    void func_0028B054();
};
void Owner::func_0028B054() {
    if (m5d4 != 0) { m2d7 = 1; return; }
    mMgr.exec();
    func_00169A80(m580);
    void** pb = &m478;
    void** pa = &m478;
    func_00168E9C(*(void**)((char*)pb + 0x108), *pa, 0);
    func_004CEAF0(*pa);
}
