// 0x674F4C  EnemyBase::EnemyBase(const ActorParam* p, s32 numStates, EnemyBase* owner)   1648 bytes
#include "actor_types.h"

EnemyBase::EnemyBase(const ActorParam* p, s32 numStates, EnemyBase* owner)
    : EnemyBase0(p, numStates, owner),
      mStateMgr(),
      mHookA(ro_006F4BA8, this, ro_0069A67C[4]),
      mHookB(ro_006F4BA8, this, ro_0069A67C[3]),
      mHookC(ro_006F77A0, this, ro_0069A67C[2]),
      m97c(0),

      m988(0),
      m98c(0), m98d(0), m98e(0), m98f(0), m990(0)
{
    m980[0] = 20;
    m980[1] = -1;
    m3ec = &mHookB;

    u32 handle = m2cc;
    func_0014EB8C(m420, m424, m3a0, &handle, m54, &mHookA, 0xffff, handle);

    m420->m61 = 0;
    m59c &= ~0x80u;

    u8 n = (u8)numStates;
    mStateMgr.mOwner = owner;
    mStateMgr.mNum = n;
    mStateMgr.init(n);

    owner->m354 = &mStateMgr;
    owner->m35a = (u16)numStates;

    mStateMgr.setName(0, SafeString("cBaseState_Wait"));
    mStateMgr.set(0, ro_0069A67C[5], ro_0069A67C[6], ro_0069A67C[1]);

    mStateMgr.setName(1, SafeString("cBaseState_Walk"));
    mStateMgr.set(1, ro_0069A67C[7], ro_0069A67C[8], ro_0069A67C[9]);

    mStateMgr.setName(2, SafeString("cBaseState_Search"));
    mStateMgr.set(2, ro_0069A67C[10], ro_0069A67C[11], ro_0069A67C[1]);

    mStateMgr.setName(3, SafeString("cBaseState_Find"));
    mStateMgr.set(3, ro_0069A67C[12], ro_0069A67C[13], ro_0069A67C[14]);

    mStateMgr.setName(4, SafeString("cBaseState_Reaction"));
    mStateMgr.set(4, ro_0069A67C[15], ro_0069A67C[16], ro_0069A67C[1]);

    mStateMgr.setName(5, SafeString("cBaseState_Die"));
    mStateMgr.set(5, ro_0069A67C[17], ro_0069A67C[18], ro_0069A67C[1]);

    mStateMgr.setName(6, SafeString("cBaseState_Appear"));
    mStateMgr.set(6, ro_0069A67C[19], ro_0069A67C[20], ro_0069A67C[21]);

    mStateMgr.setName(7, SafeString("cBaseState_GrassAppear"));
    mStateMgr.set(7, ro_0069A67C[22], ro_0069A67C[23], ro_0069A67C[24]);

    mStateMgr.setName(8, SafeString("cBaseState_AppearAfter"));
    mStateMgr.set(8, ro_0069A67C[25], ro_0069A67C[26], ro_0069A67C[27]);

    func_002AF5FC(this, 10);

    m77d = 11;
    m77e = 0xff;
    m77f = 0;

    m804 = &mHookC;
}
