// StateMgr: the per-actor state machine (enter/exec/exit pointer-to-member tables).
//
// Layout verified by every matched source that defined it locally (tools/headermigrate.py) and by
// the game's own constructors:
//
//   0x10A794  StateMgrBase::StateMgrBase()  zeroes +0x00, stores -1 at +0x04 and +0x05, then
//             zeroes +0x06, +0x08, +0x0C and +0x10   (0x18FBC0 region, 0x2CCB64, 0x62338C)
//   0x10BEC4  StateMgrBase::setStateName(idx, name)  indexes the name array with idx*0x24 and
//             copies the SafeString into it: the array is a sead::Buffer<FixedSafeString<24>>
//             (count at +0x08, pointer at +0x0C), element size 0x24 (0x10BDF0 ctor)
//   derived   the owner/enter/exec/exit pointers at +0x14..+0x20 are zeroed by the derived
//             constructor: 0x18FC10-0x18FC24 for Hookshot, 0x62338C+0x24 for NpcBase
//
// The class is a template on the owner class, because each actor's tables are member pointers of
// that actor: sources write `typedef StateMgrT<MyActor> StateMgr;`.

#ifndef STATEMGR_H
#define STATEMGR_H

#include "albw_types.h"
#include "sead_string.h"

struct StateTimeline {
    void func_00352210(bool loop, f32 frame);  // 0x352210: advance the state's timeline
};

// The part of the state machine that does not depend on the owner class.  0x14 bytes.
struct StateMgrBase {
    StateMgrBase();                                        // 0x10A794
    void setStateName(s32 idx, const sead::SafeString& name);  // 0x10BEC4

    u32 mCounter;                          // +0x00 frames in the current state
    s8 mCur;                               // +0x04
    s8 mNext;                              // +0x05
    u8 mNum;                               // +0x06 number of states
    u8 pad7;
    s32 mNameCount;                        // +0x08 sead::Buffer<FixedSafeString<24>>: count
    sead::FixedSafeString<24>* mNames;     // +0x0C  ... and array (one name per state)
    StateTimeline* mTimeline;              // +0x10
};

// The state-table construction recipe, as the game's actor constructors do it (0x2CCA44..0x2CCF0C
// for TurtleMother, the same shape in every npc/enemy constructor):
//
//   mNum   = <n>;                       // number of states
//   mOwner = this;
//   mEnter = new Func[n * 2];           // enter and exec share one allocation
//   mExec  = mEnter + n;
//   <fill the 2n enter/exec slots with the null member pointer, then overwrite per state>
//   mExit  = new Func[n];               // and fill with the null member pointer
//   mNames = new (0, 4) sead::FixedSafeString<24>[n];   // 0x10CEE0, cookie {0x24, n}
//   setStateName(i, "cState_...") for every named state
//
template <class T>
struct StateMgrT : StateMgrBase {
    typedef void (T::*Func)();

    // Derived part of the constructor: 0x18FC10-0x18FC24 zeroes exactly these four words.
    StateMgrT() : mOwner(0), mEnter(0), mExec(0), mExit(0) {}

    T* mOwner;                             // +0x14
    Func* mEnter;                          // +0x18
    Func* mExec;                           // +0x1C
    Func* mExit;                           // +0x20

    // Out of line and instantiated once per owner class: the game has one copy per actor type
    // (0x659400, 0x65CE98, 0x65D9FC, 0x6665A0, ...), which is why this is a template.
    void changeState(s32 s);

    // Two inline forms of the per-frame step both occur in matched code. They differ only in how
    // the owner/table loads are scheduled: exec() reads through `this`, execute() through a local
    // alias. Which one a caller used is visible in the bytes (register order of the table loads).
    void exec() {
        (mOwner->*mExec[mCur])();
        u32 c = ++mCounter;
        if (mTimeline) mTimeline->func_00352210(true, (f32)c);
    }
    void execute() {
        StateMgrT* s = this;
        (s->mOwner->*s->mExec[s->mCur])();
        u32 c = mCounter + 1;
        mCounter = c;
        if (mTimeline) mTimeline->func_00352210(true, (f32)c);
    }
};

#endif
