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
struct Vec3 { f32 x,y,z; };
struct Act { u8 p0[0x80]; u8 m80[0x164-0x80]; u32 m164; };
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004D7EB0(void*, u32, u32, Vec3*);
extern "C" void func_004CEAF0(Act*);
extern "C" void* func_004CF478(void*, u32, u32);
extern "C" void* func_0039B6F8(void*);
struct Owner {
    u8 p0[0x20]; u32 m20; u8 p24[0x3d0-0x24]; Vec3 m3d0; u8 p3dc[0x3e8-0x3dc]; u32 m3e8;
    u8 p3ec[0x40c-0x3ec]; StateMgr mMgr; Act* m430; u8 p434[0x480-0x434]; void* m480;
    void* func_0039B600();
};
void* Owner::func_0039B600() {
    StateMgr* s = &mMgr;
    s->exec();
    Owner* o = this;
    func_00169A80(o->m480);
    func_00168E9C(o->m480, o->m430, 0);
    Act* a = o->m430;
    a->m164 |= 0x40000000;
    func_004D7EB0(a->m80, o->m20, o->m3e8, &o->m3d0);
    func_004CEAF0(o->m430);
    if (o->mMgr.mCur != 0) return func_004CF478(o->m430, 0, 0);
    func_004CF478(o->m430, 1, 0);
    return func_0039B6F8(o);
}
