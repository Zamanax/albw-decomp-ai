// En206::En206(EnemyArg*) -- 0x00206FBC, 2268 bytes.
// Types and the recovered layout facts live in actor_types.h.
#include "actor_types.h"

struct En206 : EnemyBase {
    typedef void (En206::*Func)();

    virtual void v29();   // 2 extra slots: primary vtable = 33 entries -> secondary at +0x84
    virtual void v30();

    void cb0();    // body = 0x2069FC (delegate at 0x8E0); the invoke passes an argument
    void cb1();    // body = 0x206D28 (delegate at 0x994)

    // the 12 state handlers (enter/exec tables)
    void s0e();  void s0x();
    void s1e();  void s1x();
    void s2e();  void s2x();
    void s3e();  void s3x();
    void s4e();  void s4x();
    void s5e();  void s5x();
    void s6e();  void s6x();
    void s7e();  void s7x();
    void s8e();  void s8x();
    void s9e();  void s9x();
    void s10e(); void s10x();
    void s11e(); void s11x();

    StateMgrT<En206> mState;   // 0x8BC .. 0x8DF
    Delegate16 m8E0;           // 0x8E0
    u32 m8F0, m8F4, m8F8;      // 0x8F0 (never written by the ctor)
    u32 m8FC, m900;            // 0x8FC
    u8 m904, m905;             // 0x904
    u32 m908, m90C;            // 0x908
    u8 m910, m911;             // 0x910
    u16 m912;                  // 0x912
    u32 m914;                  // 0x914
    u8 m918;                   // 0x918
    u32 m91C, m920, m924;      // 0x91C
    f32 m928;                  // 0x928 = 1.0f
    u32 m92C, m930;            // 0x92C
    f32 m934;                  // 0x934 = 1.0f
    u32 m938;                  // 0x938
    Vec3 m93C;                 // 0x93C = zero
    Obj4* m948;                // 0x948 = getObj(0)
    Model48 m94C;              // 0x94C
    Delegate16 m994;           // 0x994

    En206(EnemyArg* arg);
};

void* operator new[](u32 size);
void* operator new[](u32 size, void* heap, s32 align);

void* func_0054D964(void* a, s32 i);
Vec3* func_00520FC0(void* a);
void func_004FB344(void* a, s32 v);
void func_004FACA4(void* a, u32 i, const void* p);
void func_004FB468(void* a);
void func_004FB0A4(void* a, f32 v);
void func_004FC5EC(void* a, u8 v);
void func_004FB30C(void* a, u32 v);
void func_004FAC70(void* a, u32 i, const void* p);
void func_004FB408(void* a);
void func_004FB070(void* a, f32 v);
void func_004FB4C4(void* a, f32 v);
void func_004FACD4(void* a, s32 v);
void* func_0054DDF4(void* a, s32 v);
void func_004F88A0(void* a, void* b);
void func_002B1FB4(void* a, s32 b, s32 c);
void func_004EDAD0(Model48* m, u32* id);
void func_004A7F00(void* mgr, Model48* m, s32 v);

extern EnemyParam data_00739DF4;           // per-class parameter block handed to EnemyBase
extern sead::SafeString data_00739D94[];   // 9 entries, set up by the static init 0x5BA5DC
extern sead::SafeString data_00739DDC[];   // 3 entries
extern void* data_00709D28;                // ModelMgr singleton pointer
extern const Vec3 data_007A9260;           // sead::Vector3f::zero

// Per-class state table (ro_00695BF0): 0xE4 bytes = { f32 mRate; En206Func mFuncs[28]; }.
// Value by value the block reads: 1.0f at +0x00, then cb0 (+4), cb1 (+0xc), state 0's
// enter/exec (+0x14/+0x1c), one null (+0x24), state 1's enter/exec, ... state 11's
// enter/exec (+0xcc/+0xd4), one null (+0xdc); the block ends at 0x695CD4, where the next
// object of the TU (1.1f...) begins.  Only the state entries are read by the ctor; mRate is
// the block's leading word (1.0f), which this constructor never loads.
static const StateTable sTable = {
    1.0f,
    {
    &En206::cb0, &En206::cb1,          // 0, 1
    &En206::s0e, &En206::s0x, 0,       // 2, 3, 4 (the null used by the exit table)
    &En206::s1e, &En206::s1x,          // 5, 6
    &En206::s2e, &En206::s2x,          // 7, 8
    &En206::s3e, &En206::s3x,          // 9, 10
    &En206::s4e, &En206::s4x,          // 11, 12
    &En206::s5e, &En206::s5x,          // 13, 14
    &En206::s6e, &En206::s6x,          // 15, 16
    &En206::s7e, &En206::s7x,          // 17, 18
    &En206::s8e, &En206::s8x,          // 19, 20
    &En206::s9e, &En206::s9x,          // 21, 22
    &En206::s10e, &En206::s10x,        // 23, 24
    &En206::s11e, &En206::s11x,        // 25, 26
    0,                                 // 27 (the null used by the enter/exec fill)
    }
};

En206::En206(EnemyArg* arg)
    : EnemyBase(arg, &data_00739DF4),
      m8E0((void*)ro_006F4758, this, sTable.mFuncs[0]),
      m8FC(0), m900(0), m904(0), m905(0), m908(0), m90C(0), m910(0), m911(0), m912(0),
      m914(0), m918(0), m91C(0), m920(0), m924(0), m928(1.0f),
      m92C(0), m930(0), m934(1.0f), m938(0),
      m93C(data_007A9260),
      m948((Obj4*)func_0054D964(this, 0)),
      m994((void*)ro_006F4758, this, sTable.mFuncs[1]) {
    if (arg->m2c == 1) {
        Vec3* p = func_00520FC0(this);
        if (p->y < 10.0f) {
            m2d7 = 1;
            return;
        }
    }
    m3ec = &m8E0;
    func_004FB344(this, 9);
    for (s32 i = 0; i < 9; i++) func_004FACA4(this, i, &data_00739D94[i]);
    func_004FB468(this);
    func_004FB0A4(this, 0.0f);
    func_004FC5EC(this, 5);
    func_004FB30C(this, 3);
    for (s32 i = 0; i < 3; i++) func_004FAC70(this, i, &data_00739DDC[i]);
    func_004FB408(this);
    func_004FB070(this, 0.0f);
    func_004FB4C4(this, 0.0f);
    func_004FACD4(this, 0);
    m91C = (u32)func_0054DDF4(this, 1);

    mState.mNum = 12;
    mState.mOwner = this;
    mState.mEnter = new Func[24];
    mState.mExec = mState.mEnter + mState.mNum;
    for (s32 i = 0; i < 12; i++) {
        mState.mEnter[i] = sTable.mFuncs[27];
        mState.mExec[i] = sTable.mFuncs[27];
    }
    mState.mExit = new Func[12];
    En206Func none = sTable.mFuncs[4];
    for (s32 i = 0; i < 12; i++) mState.mExit[i] = none;
    mState.mNames = new (0, 4) FixedSafeString24[12];
    mState.mNumNames = 12;

    mState.setStateName(0, "cState_Wait");
    En206Func e0 = sTable.mFuncs[2];
    En206Func x0 = sTable.mFuncs[3];
    mState.mEnter[0] = e0;
    mState.mExec[0] = x0;
    mState.mExit[0] = none;
    mState.setStateName(1, "cState_Kyorokyoro");
    En206Func e1 = sTable.mFuncs[5];
    En206Func x1 = sTable.mFuncs[6];
    mState.mEnter[1] = e1;
    mState.mExec[1] = x1;
    mState.mExit[1] = none;
    mState.setStateName(2, "cState_Walk");
    En206Func e2 = sTable.mFuncs[7];
    En206Func x2 = sTable.mFuncs[8];
    mState.mEnter[2] = e2;
    mState.mExec[2] = x2;
    mState.mExit[2] = none;
    mState.setStateName(3, "cState_Stop");
    En206Func e3 = sTable.mFuncs[9];
    En206Func x3 = sTable.mFuncs[10];
    mState.mEnter[3] = e3;
    mState.mExec[3] = x3;
    mState.mExit[3] = none;
    mState.setStateName(4, "cState_Reaction");
    En206Func e4 = sTable.mFuncs[11];
    En206Func x4 = sTable.mFuncs[12];
    mState.mEnter[4] = e4;
    mState.mExec[4] = x4;
    mState.mExit[4] = none;
    mState.setStateName(5, "cState_Die");
    En206Func e5 = sTable.mFuncs[13];
    En206Func x5 = sTable.mFuncs[14];
    mState.mEnter[5] = e5;
    mState.mExec[5] = x5;
    mState.mExit[5] = none;
    mState.setStateName(6, "cState_PetrificationStart");
    En206Func e6 = sTable.mFuncs[15];
    En206Func x6 = sTable.mFuncs[16];
    mState.mEnter[6] = e6;
    mState.mExec[6] = x6;
    mState.mExit[6] = none;
    mState.setStateName(7, "cState_PetrificationStop");
    En206Func e7 = sTable.mFuncs[17];
    En206Func x7 = sTable.mFuncs[18];
    mState.mEnter[7] = e7;
    mState.mExec[7] = x7;
    mState.mExit[7] = none;
    mState.setStateName(8, "cState_PetrificationShake");
    En206Func e8 = sTable.mFuncs[19];
    En206Func x8 = sTable.mFuncs[20];
    mState.mEnter[8] = e8;
    mState.mExec[8] = x8;
    mState.mExit[8] = none;
    mState.setStateName(9, "cState_PetrificationReveive");
    En206Func e9 = sTable.mFuncs[21];
    En206Func x9 = sTable.mFuncs[22];
    mState.mEnter[9] = e9;
    mState.mExec[9] = x9;
    mState.mExit[9] = none;
    mState.setStateName(10, "cState_Turn");
    En206Func e10 = sTable.mFuncs[23];
    En206Func x10 = sTable.mFuncs[24];
    mState.mEnter[10] = e10;
    mState.mExec[10] = x10;
    mState.mExit[10] = none;
    mState.setStateName(11, "cState_UniqueDie");
    En206Func e11 = sTable.mFuncs[25];
    En206Func x11 = sTable.mFuncs[26];
    mState.mEnter[11] = e11;
    mState.mExec[11] = x11;
    mState.mExit[11] = none;

    if (arg->m2a != 0) {
        m914 = 0x32;
        func_004F88A0(this, (void*)m91C);
        mState.changeState(7);
    } else {
        mState.changeState(1);
    }
    m468 = 0.5f;
    m853 = 1;
    func_002B1FB4(this, -1, 0x80);
    m77d = 0;
    m77e = 0xff;
    m77f = 0;
    m948->m4 = m3d0;
    u16 mid = 0xa4;
    m948->m28 = mid;
    m94C.m18 = m948;
    u32 id = m2cc;
    func_004EDAD0(&m94C, &id);
    m94C.m2c = m54;
    func_004A7F00(data_00709D28, &m94C, 2);
    m94C.m44 = 0;
    m448 = &m994;
}
