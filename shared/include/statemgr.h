// StateMgr: the per-actor state machine (enter/exec/exit pointer-to-member tables).
//
// Layout verified by every matched source that defined it locally (tools/headermigrate.py).
// A template on the owner class, because each actor's tables are member pointers of that actor:
// sources write `typedef StateMgrT<MyActor> StateMgr;`.

#ifndef STATEMGR_H
#define STATEMGR_H

#include "albw_types.h"

struct StateTimeline {
    void func_00352210(bool loop, f32 frame);  // 0x352210: advance the state's timeline
};

template <class T>
struct StateMgrT {
    typedef void (T::*Func)();

    u32 mCounter;              // +0x00 frames in the current state
    s8 mCur;                   // +0x04
    s8 mNext;                  // +0x05
    u8 mNum;                   // +0x06
    u8 pad7;
    u32 mNames[2];             // +0x08
    StateTimeline* mTimeline;  // +0x10
    T* mOwner;                 // +0x14
    Func* mEnter;              // +0x18
    Func* mExec;               // +0x1C
    Func* mExit;               // +0x20

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
