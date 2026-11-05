// Types recovered from TurtleMother::TurtleMother(ActorParam*) at 0x2CC800 (2836 bytes) and its
// base constructor NpcBase<T>::NpcBase(ActorParam*, s32, s32, const NpcInitParam&) at 0x623368.
//
// Every layout claim below is backed by the instruction addresses that write or read it in the
// target disassembly (logs/manual/H_002CC800/disasm.txt).  Nothing here is guessed from names.
//
//   this+0x000  primary vtable          <- 0x2CC850 str r1,[r0],   r1 = ro_006DD280
//   this+0x320  secondary vtable        <- 0x2CC854 str r2,[r0,#0x320], r2 = ro_006DD280+0xb8
//   this+0x960  StateMgrT<TurtleMother> <- 0x2CCB64/0x2CCA74 (StateMgrBase ctor runs at 0x960 in
//              0x62338C: r0 = this+0x320+0x640), mNum/mOwner/mEnter/mExec/mExit/names all written here
//   this+0x984  s32 saved init state    <- 0x6233AC str r4,[r1] with r1 = stateMgr+0x24
//   NpcBase ends at 0x988 (StateMgr is 0x24 bytes: mExit at +0x20), the derived members follow.

#ifndef ACTOR_TYPES_H
#define ACTOR_TYPES_H

#include "albw_types.h"
#include "vec3.h"

// armcc 4.1's __va_start only accepts a pointer va_list in this build (a
// `typedef struct __va_list { void* __ap; } va_list;` makes the *first* variadic function of a
// translation unit fail with #928 and makes the type incompatible with __va_start).  The game's
// call site passes the address of the va_list object (0x2CCF64 add r2,sp,#4), i.e. formatV takes
// it by reference, and 0x111A20 forwards that same pointer straight to the C library va_arg user.
typedef void* va_list;
#define va_start(ap, parmN) __va_start(ap, parmN)
#define va_end(ap) ((void)(ap))

namespace sead {
// sead::SafeString: vptr + text pointer, exactly the object built on the stack before each
// StateMgrBase::setStateName call (0x2CCB78: text at sp+0x64, 0x6F5988 stored at sp+0x60).
class SafeString {
public:
    SafeString() : mStringTop(0) {}
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;              // +0x04
};

// sead::BufferedSafeString adds the capacity; a local of this shape is built at sp+0x68 before
// sead::BufferedSafeStringBase<char>::formatV(0x111A20) at 0x2CCF70: vptr 0x6F6FE8 at +0,
// text = own buffer at +4, capacity 0x40 at +8, buffer at +0xc.
class BufferedSafeString : public SafeString {
public:
    BufferedSafeString() : mBufferSize(0) {}
    virtual void assureTerminationImpl_() const;
    void formatV(const char* fmt, va_list& args); // 0x111A20
    __forceinline void format(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        formatV(fmt, args);
        va_end(args);
    }
    s32 mBufferSize;                     // +0x08
};

// FixedSafeString<N>: BufferedSafeString with the character buffer inline.  The ctor is
// 0x10BDF0 (seen at 0x2CCB48 passed to __aeabi_vec_ctor) and sizes are 0x24 bytes for N = 24
// (0x2CCB3C mov r1,#0x24) and 0x40 bytes for N = 0x40 (0x2CCF44 mov r2,#0x40).
template <int N>
class FixedSafeString : public BufferedSafeString {
public:
    __forceinline FixedSafeString() {
        mStringTop = mBuf;
        mBufferSize = N;
        mBuf[0] = 0;
        mBuf[N - 1] = 0;
    }
    virtual void assureTerminationImpl_() const;
private:
    char mBuf[N];
};
}  // namespace sead

// Parameter block handed to NpcBase by every npc constructor.
// Evidence, 0x2CC820-0x2CC83C: 12 zero bytes at sp+0xe8 (stm of three zeroed registers),
// byte 0 at sp+0xf4 and byte 1 at sp+0xf5; the address of that block is passed as the 5th
// argument of NpcBase's constructor (0x2CC830 str r1,[sp]), which forwards it in r3 to the
// grand-parent constructor at 0x4C18E0 (0x623374 ldr r3,[sp,#8]).
struct NpcInitParam {
    u32 m0, m4, m8;                      // +0x00..0x0b, zeroed
    u8 mC;                               // +0x0c, zeroed
    u8 mD;                               // +0x0d, set to 1

};

// One actor parameter record (only the members this constructor reads).
// 0x2CC998 ldr r0,[r6,#0x29c] / 0x2CC9A4 [r6,#0x2a0]: two s32 rail indices tested with
// "cmp r0,#0; blt" before the rail is copied.
struct ActorParam {
    u8 pad000[0x29c];
    s32 m29c;                            // +0x29c rail index (negated value = "no rail")
    s32 m2a0;                            // +0x2a0 second check
};

// A bcl/kcl model holder, 0x48 bytes (allocation size at 0x2CC8C0, 0x2CCF20, 0x2CCFBC).
// ctor 0x4EDC9C, load 0x4EDB28, ModelMgr::regist 0x4A7F00.
struct Model {
    Model();                             // 0x4EDC9C
    u8 pad000[0x10];
    void* m10;                           // +0x10 cleared/used by 0x4ED9C8 (0x4ED9D0)
    void* m14;                           // +0x14 matrix node (0x2CD158 ldr r0,[r0,#0x14])
    void* m18;                           // +0x18 (0x4ED9DC)
    u8 pad01c[4];
    u32 m20;                             // +0x20 id, set by 0x4EDAD0 (0x4EDADC str r0,[r4,#0x20])
    u8 pad024[4];
    void* m28;                           // +0x28 callback object (0x2CD138 str r1,[r0,#0x28])
    u16 m2c;                             // +0x2c actor id (0x2CCFA4 strh r1,[r0,#0x2c])
    u8 pad02e[0x16];
    u8 m44;                              // +0x44 visible flag (0x2CD20C strb sb,[r0,#0x44])
    void load(const sead::SafeString& path);  // 0x4EDB28
};

// Res7A0::find(0x564A78) handles, stored at this+0x9d4/0x9d8/0x9dc (0x2CD2A4, 0x2CD2C0, 0x2CD2DC).
// The resource object itself lives at this+0x7a0 (0x2CD29C ldr r0,[r6] with r6 = this+0x7a0).

// One rail: points PtrArray {count at +0x20, T** at +0x28} (0x2CC9D8 ldr r1,[r0,#0x28] /
// 0x2CC9DC ldr r0,[r0,#0x20]); each point's position is a Vec3 at +0x18 (0x2CCA00 vldr s1,[ip,#0x18]).
struct RailPoint {
    u8 pad000[0x18];
    Vec3 pos;                            // +0x18
};

// PtrArray<T>: count at +0x00, T** at +0x08 (0x2CC9C0 ldr r2,[r0] / 0x2CC9C8 ldrhi r0,[r0,#8]),
// indexed with an unsigned compare: rails->count > i (0x2CC9C4 cmp r2,r1 / ldrhi).
template <class T>
struct PtrArray {
    u32 count;                           // +0x00
    u8 pad004[4];
    T** items;                           // +0x08
    T* at(u32 i) { if (i < count) return items[i]; return 0; }
};

struct Rail {
    u8 pad000[0x20];
    u32 pointCount;                      // +0x20
    u8 pad024[4];
    RailPoint** points;                  // +0x28
};

// FlagMgr singleton: data_0070B728 holds the manager, check(id) is 0x584B94
// (0x2CC930 ldr r0,[r5]; 0x2CC934 bl 0x584B94 with r1 = 0x283).
struct FlagMgr {
    bool check(s32 id);                  // 0x584B94
};

// The 0x48 byte helper allocated at this+0x9bc (0x2CC8C0 mov r0,#0x48, ctor 0x34CAA0).
// ctor stores: +0x00/+0x04 = 0, +0x20 = 0x0f, +0x21 = +0x22 = -1, +0x30 = 0,
// +0x32 = 1, +0x34 = 1.0f, then calls 0x34CA24.
struct NpcControl {
    NpcControl();                        // 0x34CAA0
    u32 m00, m04;                        // +0x00
    u8 pad008[0x18];
    u8 m20;                              // +0x20 = 0x0f
    s8 m21, m22;                         // +0x21 = +0x22 = -1
    u8 pad023[0xd];
    u16 m30;                             // +0x30 = 0
    u16 m32;                             // +0x32 = 1
    f32 m34;                             // +0x34 = 1.0f
    u8 pad038[0x10];                     // +0x38..0x47 (allocation size 0x48 at 0x2CC8C0)
};

// The callback object embedded at this+0x9c0: {vptr = ro_006F7C98, owner = this}
// (0x2CC8FC stm r0,{r1,r4}); a Model points at it (0x2CD138 str r1,[r0,#0x28]).
struct NpcListener {
    NpcListener(void* o) : mOwner(o) {}
    virtual void invoke();
    void* mOwner;                        // +0x04
};

// A 0x50 entry Vec3 array with a clamping accessor: 0x2CCA0C "addlo ip,r2,r2,lsl #1" (index*3)
// and 0x2CCA18 "movhs ip,r0" (out of range -> element 0), compare is "cmp r2,#0x50".
template <int N>
struct Vec3Table {
    Vec3 d[N];
    Vec3& at(u32 i) { if (i < (u32)N) return d[i]; return d[0]; }
};

struct Mtx33 { f32 m[9]; };
struct Mtx34 { f32 m[12]; };
Mtx33* getRot(Mtx33* out, const Mtx34* in);   // 0x1151D8

// ---------------------------------------------------------------------------------------------
// State machine.  Matches shared/include/statemgr.h except for the name table, which is a
// sead::Buffer of 11 FixedSafeString<24> (not a raw u32[2]):
//
//   0x2CCB08  cmp sl,#0 / mov r2,#4 / mov r1,#0 / mov r0,#8 / ble   -> allocBuffer(11) with an
//             empty-buffer fallback of 8 bytes, heap 0, align 4          (0x10CEE0)
//   0x2CCB3C  mov r1,#0x24  element size                              (FixedSafeString<24>)
//   0x2CCB40  stm sb,{r1,sl}                allocation cookie {0x24, 11}
//   0x2CCB48  ldr r1,=0x10BDF0              FixedSafeString<24> ctor  (__aeabi_vec_ctor)
//   0x2CCB58  strne sl,[r6,#8]!  /  strne r0,[r6,#4]   {count at +0x08, pointer at +0x0c}
// ---------------------------------------------------------------------------------------------
struct StateTimeline {
    void func_00352210(bool loop, f32 frame);      // 0x352210
};

struct StateNames {                                 // sead::Buffer<sead::FixedSafeString<24>>
    u32 mCount;                                     // +0x00
    sead::FixedSafeString<24>* mPtr;                // +0x04
    void allocBuffer(s32 n);
};

template <class T>
struct ActorStateMgr {
    typedef void (T::*Func)();

    u32 mCounter;                                   // +0x00
    s8 mCur;                                        // +0x04
    s8 mNext;                                       // +0x05
    u8 mNum;                                        // +0x06 = 11 (0x2CCA4C strb sl,[r4,#0x966])
    u8 pad7;                                        // +0x07
    StateNames mNames;                              // +0x08
    StateTimeline* mTimeline;                       // +0x10
    T* mOwner;                                      // +0x14 = this (0x2CCA58)
    Func* mEnter;                                   // +0x18 (0x2CCA60)
    Func* mExec;                                    // +0x1c = mEnter + mNum (0x2CCA70)
    Func* mExit;                                    // +0x20 (0x2CCAB4)

    void setStateName(s32 idx, const sead::SafeString& name);   // 0x10BEC4
};

// ---------------------------------------------------------------------------------------------
// NpcBase<T>
//
// Base constructor 0x623368 (80 bytes):
//   bl 0x4C18E0(this, param, initState, arg, np);         // grand parent
//   *(void**)this         = ro_006CB858;                  // 0x62337C
//   *(void**)(this+0x320) = ro_006CB858 + 0xb8;           // 0x623384 (r1+0xb8)
//   StateMgrBase::StateMgrBase(this+0x960);               // 0x62338C, r0 = this+0x320+0x640
//   stateMgr.mOwner = mEnter = mExec = mExit = 0;         // +0x14..+0x20
//   *(s32*)(this+0x984) = initState;                      // 0x6233AC
//
// The two vtable stores mean NpcBase derives from two polymorphic bases: the primary one at
// +0x000 and a second one at +0x320.  Their vtables sit 0xb8 bytes apart, i.e. the primary
// vtable has (0xb8 - 8) / 4 = 44 virtual slots (same arithmetic as the matched Player ctor,
// where 21 slots put the secondary vtable at +0x5c).
// ---------------------------------------------------------------------------------------------

// Second polymorphic base of NpcBase; its complete subobject occupies +0x320..+0x960.
struct NpcSecondBase {
    virtual void sb0();
    u8 pad004[0x63c];                    // size 0x640: 0x320 + 0x640 = 0x960
};

template <class T>
class NpcBase : public NpcSecondBase {
public:
    NpcBase(ActorParam* p, s32 initState, s32 arg, const NpcInitParam& np);  // 0x623368

    // primary vtable slots of the whole hierarchy: (0xb8 - 8) / 4 = 44
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();

    typedef ActorStateMgr<T> StateMgr;
    typedef typename StateMgr::Func Func;

    u8 pad004[0x50];
    u16 mActorId;                        // +0x054  (0x2CCF98 ldrh r1,[r4,#0x54])
    u8 pad056[0x2cc - 0x56];
    u32 m2cc;                            // +0x2cc  (0x2CCF80 ldr r0,[r4,#0x2cc])
    u8 pad2d0[0x320 - 0x2d0];

    // +0x320: NpcSecondBase subobject (contains its own vptr); members continue
    u8 pad324[0x354 - 0x324];
    void* m354;                          // +0x354  = &mStateMgr (0x2CCB64)
    u8 pad358[2];
    u16 m35a;                            // +0x35a  = 11 (0x2CCB74 strh r0,[r1,#0x5a], r1 = this+0x300)
    u8 pad35c[0x3ac - 0x35c];
    f32 m3ac;                            // +0x3ac  (0x2CD28C vstr s0,[r4,#0x3ac])
    u8 pad3b0[0x3d0 - 0x3b0];
    u8 m3d0[0x18];                       // +0x3d0  matrix passed to 0x43625C
    u32 m3e8;                            // +0x3e8  (0x2CC920 ldr r0,[r4,#0x3e8])
    u8 pad3ec[0x7a0 - 0x3ec];
    u32 m7a0;                            // +0x7a0  resource handle/pointer (0x2CD24C ldr r0,[r4,#0x7a0])
    u8 pad7a4[0x853 - 0x7a4];
    u8 m853;                             // +0x853  (0x2CD1E0 strb r0,[r4,#0x853])
    u8 pad854[3];
    u8 m857;                             // +0x857  (0x2CD234 / 0x2CD2E0)
    u8 pad858[0x8ac - 0x858];
    u32 m8ac;                            // +0x8ac  flag word (orr #0x10, bic #8, orr #0x2c40)
    u8 pad8b0[0x960 - 0x8b0];

    ActorStateMgr<T> mStateMgr;          // +0x960  (0x24 bytes)
    s32 mInitState;                      // +0x984
};

// ---------------------------------------------------------------------------------------------
// Recovered constants and orderings (for any other NPC constructor that reuses these types)
//
// 1. The state function table.  0x2CCA68 "ldr fp,[pc,#0x190]" loads the address of the game's
//    member-function-pointer table at 0x6A0698; every per-state assignment reads fp+8*index.
//    Dumped from the image (25 entries, all 8-byte {function, 0} member pointers):
//      0  0x2CC144   1 0x622C50   2 0x6231A0   3 null       4 0x622CF0   5 0x6231B0
//      6  0x622E78   7 0x6225C0   8 0x2CC464   9 0x2CC188  10 0x623088  11 0x622C04
//     12  0x62319C  13 0x622BDC  14 0x2CC550  15 0x2CC18C  16 0x2CC5CC  17 0x2CC4BC
//     18  0x2CC564  19 0x2CC1DC  20 0x2CC568  21 0x2CC1E0  22 0x2CC7B0  23 0x2CC644
//     24 null      (the fill value used for the 11 unused enter/exec slots, 0x2CCA7C)
//    The table ends at 0x6A0758; 0x6A0760 starts the next actor's table (0x614xxx functions).
//
// 2. Table setup (0x2CCA44..0x2CCF0C), in this exact order:
//      mNum = 11; mOwner = this; mEnter = new Func[22]; mExec = mEnter + 11;
//      fill both with entry 24 (single loop, 16 bytes per iteration, 0x2CCA7C);
//      mExit = new Func[11]; fill with entry 3 (0x2CCAA4);
//      names = Buffer<FixedSafeString<24>>::allocBuffer(11) (0x2CCB08);
//      then, per state: write mEnter/mExec/mExit from the entries above, then setStateName:
//        state 0  entries 1,2,3        name "cState_Wait"
//        state 1  entries 4,5,3        name "cState_Walk"
//        state 2  entries 6,7,3        name "cState_Event"
//        state 8  entries 8,9,10       name "cState_EventEnd"      <- index 8, not 3
//        state 4  entries 11,12,13     name "cState_Hide"
//        state 5  entries 14,15,3      name "cState_CheckPlayer"
//        state 6  entries 16,17,3      name "cState_TurtleDocking"
//        state 7  entries 18,19,3      name "cState_DockingWait"
//        state 8  entries 8,9,3        name "cState_EventEnd"      <- state 8 written twice
//        state 9  entries 20,21,3      name "cState_WalkingLake"
//        state 10 entries 22,23,3      name "cState_ReCheckPlayerCancel"
//      State 3 is never written and never named (it keeps the fill value).
//      (The two "8" entries and the missing "3" are in the original code: the 4th fill really
//       stores at offset 0x40 = 8*8 at 0x2CCAEC..0x2CCD08, and the 4th call really passes
//       r1 = 8 at 0x2CCCE0.)
//
// 3. Strings and their use sites:
//      0x2CCC34 "cState_Wait"      0x2CCC40 "cState_Walk"        0x2CD020 "cState_Event"
//      0x2CD030 "cState_EventEnd"  0x2CD040 "cState_Hide"        0x2CD04C "cState_CheckPlayer"
//      0x2CD060 "cState_TurtleDocking"  0x2CD078 "cState_DockingWait"
//      0x2CD08C "cState_WalkingLake"    0x2CD0A0 "cState_ReCheckPlayerCancel"
//      0x2CD0BC "Actor/TurtleMother_0.kcl"  0x2CD0E0 "Actor/TurtleMother_1.kcl"
//      0x2CD2FC "TurtleL"  0x2CD304 "TurtleM"  0x2CD30C "TurtleS"   (Res7A0::find at 0x2CD290)
//      0x2CCC14 a 7-character Shift-JIS tag passed to func_004BE114 (0x2CC96C/0x2CC994)
//
// 4. Flag ids checked at 0x2CC928/0x2CC944/0x2CC954: 0x283, 0x284, 0x285; all three set makes
//    m9b1 true, which selects the "state 9 / m853 = 3" branch at 0x2CD1D4 instead of
//    "state 10 / m857 = 0" (0x2CD220).

#endif
