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
#include "sead_heap.h"
#include "sead_string.h"

struct StateTimeline {
    void func_00352210(bool loop, f32 frame);  // 0x352210: advance the state's timeline
};

// The part of the state machine that does not depend on the owner class.  0x14 bytes.
struct StateMgrBase {
    StateMgrBase();                                        // 0x10A794
    void setStateName(s32 idx, const sead::SafeString& name);  // 0x10BEC4

    // sead::Buffer::allocBuffer on the flattened name buffer. heap/align are parameters, so the
    // inline is expanded late and their registers are set before the size test (0x66D9C4).
    void allocNames(s32 size, sead::Heap* heap, s32 align = 4) {
        if (size > 0) {
            sead::FixedSafeString<24>* names = new (heap, align) sead::FixedSafeString<24>[size];
            if (names) {
                mNameCount = size;
                mNames = names;
            }
        }
    }

    u32 mCounter;                          // +0x00 frames in the current state
    s8 mCur;                               // +0x04
    s8 mNext;                              // +0x05
    u8 mNum;                               // +0x06 number of states
    u8 pad7;
    s32 mNameCount;                        // +0x08 sead::Buffer<FixedSafeString<24>>: count
    sead::FixedSafeString<24>* mNames;     // +0x0C  ... and array (one name per state)
    StateTimeline* mTimeline;              // +0x10
};

// The state-table construction recipe: init() below. The game has it out of line once per owner
// type (0x0066D8D0, 0x0066739C: `init(this, n)` with n a byte temporary, so `const u8&`) and inlined
// into most npc/enemy constructors (~295 unmatched functions contain the name-table half).
// Proven on 0x0066D8D0 up to the null member-pointer constants: those are loaded from the owner
// TU's member-pointer constant table (ro_006A5E3C + 0xB8 / + 0x10), whose offsets depend on every
// other function of that TU, so the out-of-line copy only matches compiled with its owner's TU.
template <class T>
struct StateMgrT : StateMgrBase {
    typedef void (T::*Func)();

    // Derived part of the constructor: 0x18FC10-0x18FC24 zeroes exactly these four words.
    StateMgrT() : mOwner(0), mEnter(0), mExec(0), mExit(0) {}

    // A helper with parameters, so it is inlined late: the loop does not know that the enter/exec
    // count (2n) is even and keeps the odd-element step (`tst rN, #1`), as the game does.
    static void clearTable(Func* table, s32 n) {
        for (s32 i = 0; i < n; i++) table[i] = 0;
    }

    void init(T* owner, const u8& n) {
        mNum = n;
        mOwner = owner;
        s32 n2 = mNum * 2;
        Func* enter = new Func[n2];        // enter and exec share one allocation
        mEnter = enter;
        mExec = enter + mNum;
        clearTable(enter, n2);
        s32 n1 = mNum;
        Func* exit = new Func[n1];
        mExit = exit;
        clearTable(exit, n1);
        allocNames(n, 0);                  // 0x10CEE0 + cookie {0x24, n} + vec_ctor(0x10BDF0)
    }

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
