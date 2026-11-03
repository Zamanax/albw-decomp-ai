typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef float f32;

extern void* data_0070B850;
void func_0066E7A0(void* self, s8 s);
u32 func_005228A4(void* p, u32 a);

struct Timeline {
    void func_00352210(bool b, f32 frame);
};
template <typename T>
struct StateMgr {
    typedef void (T::*Func)();
    u32 mCounter;        // +0
    s8 mCur;             // +4
    s8 mNext;            // +5
    u8 mNum;             // +6
    char pad7[0x10 - 7];
    Timeline* mTimeline; // +0x10
    T* mOwner;           // +0x14
    Func* mEnter;        // +0x18
    Func* mExec;         // +0x1c
    Func* mExit;         // +0x20
    void execute() {
        (mOwner->*mExec[mCur])();
        ++mCounter;
        if (mTimeline)
            mTimeline->func_00352210(true, (f32)mCounter);
    }
};
struct Sub {
    char pad[0x3c];
    s8 m3c;
};
struct Cls7AA0 {
    char pad0[0x10];
    u32 m10;
    char pad14[0xcc - 0x14];
    StateMgr<Cls7AA0> mB;     // +0xcc
    StateMgr<Cls7AA0> mState; // +0xf0
    char pad114[0x1f4 - 0x114];
    Sub* m1f4;
    Sub* m1f8;
    void func_0047BF90();
};
void Cls7AA0::func_0047BF90() {
    if (mState.mCur != 0xb) {
        if (func_005228A4(data_0070B850, m10) == 0) {
            if (mB.mCur == 2) {
                func_0066E7A0(&mState, 0xb);
            } else if ((u32)(m1f4->m3c - 1) < 5u || (u32)(m1f8->m3c - 1) < 5u) {
                func_0066E7A0(&mState, 0xb);
                func_0066E7A0(&mB, 2);
            }
        }
    }
    mState.execute();
}
