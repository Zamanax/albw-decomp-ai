// Types recovered from Hookshot::Hookshot() 0x18FBA8 (3508 B) and its callees.
// Every offset below is backed by an instruction address in the target function
// unless another function is named.  Written so other actor constructors can
// include it: nothing here is Hookshot-specific except the `Hookshot` class
// itself and the two state-table statics.
//
// Include order: this header needs "vec3.h" (Vec3) from shared/include.

#ifndef HOOKSHOT_ACTOR_TYPES_H
#define HOOKSHOT_ACTOR_TYPES_H

#include "vec3.h"

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

struct ActorParam;
struct Heap;
// 0x10BA78: operator new[](u32 size) -- the *second* argument is ignored by the
// callee (it only forwards r0 to the heap's virtual alloc(size, 4)), but the
// original call sites still pass one in r1.
void* operator new[](u32, Heap*);
// 0x10CEE0: operator new[](u32 size, Heap* heap, s32 align) -- heap 0 = current.
void* operator new[](u32, Heap*, s32);

namespace sead {
// 8 bytes: {vptr, mStringTop}.  vtable ro_6F5988 (0x18FDD8 stores it into the
// stack temporary that is passed to StateMgrBase::setStateName).
class SafeString {
public:
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
}  // namespace sead

// 0x24 bytes.  ctor 0x10BDF0 (passed to __aeabi_vec_ctor_nocookie_nodtor at
// 0x190194 with size 0x24).  StateMgrBase::setStateName (0x10BEC4) indexes the
// array with `idx*0x24`, which fixes the element size.
struct FixedSafeString24 {
    FixedSafeString24();
    char pad[0x24];
};

// ---------------------------------------------------------------------------
// Actor base chain.  ctor 0x150E40 (called at 0x18FBB8); it calls 0x4ED00C and
// installs two vtables, so the class has a second base at +0x320.
// ---------------------------------------------------------------------------
struct Obj2D0 { char pad[0x18]; char m18[1]; };
struct StateMgr;

struct ActorBaseA {
    // vtable[0] is the RTTI check: 0x18FE60 does `blx r2` with r0 = actor,
    // r1 = &static TypeInfo, so slot 0 is `isDerived(const Interface*)`.
    virtual bool checkDerived(const void* t) const;
    virtual void v1();
    virtual void v2();
    virtual ~ActorBaseA();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    virtual void v9();  virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    void func_004ECF6C();
    char pad004[0x54 - 4];
    s16 m54;                       // 0x1904FC `ldrsh r0, [r4, #0x54]`
    char pad56[0x2cc - 0x56];
    u32 m2cc;                      // 0x190448 `ldr r0, [r4, #0x2cc]`
    Obj2D0* m2d0;
    char pad2d4[0x2d7 - 0x2d4];
    u8 m2d7;                       // 0x18FE78 `strbeq r0, [r4, #0x2d7]`
    char pad2d8[0x320 - 0x2d8];
};
struct ActorBaseB {
    virtual void b0();
};

// 0x40C bytes.  The ctor 0x150E40 initialises everything up to 0x3f8, so all of
// the fields below belong to the base, not to Hookshot.
class ActorBase : public ActorBaseA, public ActorBaseB {
public:
    ActorBase(ActorParam* p);
    virtual ~ActorBase();
    char pad324[0x354 - 0x324];
    StateMgr* m354;                // 0x1901B8 `str r0, [r4, #0x354]`
    char pad358[2];
    u16 m35a;                      // 0x1901C0 `strh r1, [r2, r4]` (r2 = 0x35a)
    char pad35c[0x3a0 - 0x35c];
    u32 m3a0;                      // 0x1904B0
    u32 m3a4;                      // 0x1904B4
    char pad3a8[0x3d0 - 0x3a8];
    Vec3 m3d0;                     // 0x18FEC8 `add r0, r4, #0x3d0`
    f32 m3dc, m3e0, m3e4;          // 0x190738/0x19073C/0x190740
    u32 m3e8;                      // 0x18FEA8 `ldr r2, [r4, #0x3e8]` (angle index)
    char pad3ec[0x40c - 0x3ec];
};

// ---------------------------------------------------------------------------
// Delegate: 16 bytes {vptr, mObj, mFunc}.  vtable ro_6F4554; its slot 0
// (0x6830E8) decodes the member-function pointer as
//     mObj == 0            -> return 0
//     mFunc == 0 && !(adj&1) -> return 0
//     r0 = mObj + (adj >> 1);  if (adj & 1) r0 = *(void**)r0, fn = r0[mFunc/4]
// so a *virtual* member function pointer is stored as
//     { vtable_byte_offset, (this_adjustment << 1) | 1 }
// Evidence: 0x18FBD4 `ldm r8, {r1, r3}` loads {0x4c, 1} from ro_6A16B8+0x00 and
// 0x18FBE4 stores it at 0x414/0x418; 0x18FBF0 loads {0x50, 1} from +0x08.
// ---------------------------------------------------------------------------
class Hookshot;
typedef void (Hookshot::*HFunc)();

struct Delegate {
    Delegate() : mObj(0), mFunc(0) {}
    Delegate(Hookshot* o, HFunc f) : mObj(o), mFunc(f) {}
    virtual void invoke();
    Hookshot* mObj;
    HFunc mFunc;
};

// ---------------------------------------------------------------------------
// State machine.  StateMgrBase ctor 0x10A794 zeroes +0x00, sets +0x04/+0x05 to
// -1, and zeroes +0x06, +0x08, +0x0C, +0x10 -> 0x14 bytes.
// +0x08/+0x0C are a sead::Buffer<FixedSafeString<24>>: count then pointer
// (0x10BEC4 reads [r0+8] as the count and [r0+0xC] as the base, stride 0x24).
// The derived part adds owner/enter/exec/exit at +0x14..+0x20 (0x18FC10-0x18FC24
// zeroes exactly those four words), total 0x24 bytes.
// NOTE: shared/include/statemgr.h models +0x08 as `u32 mNames[2]`; the layout and
// size are identical, but a constructor that *fills* the names needs the Buffer
// form.  See REPORT.json header_changes_needed.
// ---------------------------------------------------------------------------
struct StateTimeline {
    void func_00352210(bool loop, f32 frame);
};

struct StateMgrBase {
    StateMgrBase();                // 0x10A794
    u32 mCounter;                  // +0x00
    s8 mCur;                       // +0x04
    s8 mNext;                      // +0x05
    u8 mNum;                       // +0x06  (0x190088 `strb r0, [r4, #0x4a2]` = 8)
    u8 pad7;
    u32 mNameCount;                // +0x08  (0x1901A4 `strne sl, [r5, #8]!` = 8)
    FixedSafeString24* mNames;     // +0x0C  (0x1901A8 `strne r0, [r5, #4]`)
    StateTimeline* mTimeline;      // +0x10
};

struct StateMgr : StateMgrBase {
    typedef void (Hookshot::*Func)();
    StateMgr() : mOwner(0), mEnter(0), mExec(0), mExit(0) {}
    Hookshot* mOwner;              // +0x14  (0x190090 `str r4, [r4, #0x4b0]`)
    Func* mEnter;                  // +0x18  (0x190098 `str r0, [r5, #0x18]`)
    Func* mExec;                   // +0x1C  (0x1900A4 `str r1, [r5, #0x1c]`)
    Func* mExit;                   // +0x20  (0x1900EC `str r0, [r5, #0x20]`)
    void setStateName(s32 idx, const sead::SafeString& name);   // 0x10BEC4
};

// ---------------------------------------------------------------------------
// 0x438: 0x64-byte sub object, ctor 0x4EE484 (calls 0x10DA7C(this, 0, 3)).
// Fields proven by the ctor and by 0x4EDEA0 / 0x14EB8C:
//   +0x10  void*  (0x190444 `str r0, [r1, #0x10]` = m42c[i])
//   +0x14  u32    (0x4EDEA8 `str r0, [r4, #0x14]` = *handle)
//   +0x18  u16    (0x4EDED0 `strhne r0, [r4, #0x18]` = actor->0x54)
//   +0x22  u8     (0x1906C8 `strb r1, [r0, #0x22]` = 5)
//   +0x32  u16    (0x1906B8 `strh r1, [r0, #0x32]` = 0x920)
// ---------------------------------------------------------------------------
struct Sub438 {
    Sub438();
    char pad0[0x10];
    void* m10;
    u32 m14;
    u16 m18;
    char pad1a[0x22 - 0x1a];
    u8 m22;
    char pad23[0x32 - 0x23];
    u16 m32;
    char pad34[0x64 - 0x34];
};

// 0x435714(kind*) allocates one of these; 0x4356B4(o) activates it.
// 0x18FF60/0x18FF68/0x18FF6C store a Vec3 at +0x04, 0x18FF7C stores 0.22f at
// +0x58, 0x1906E4 reads/writes a flag word at +0x2C.
struct Obj435714 {
    char pad0[4];
    Vec3 m4;
    char pad10[0x2c - 0x10];
    u32 m2c;
    char pad30[0x58 - 0x30];
    f32 m58;
};

// Static RTTI root used by the dynamic_cast at 0x18FE20-0x18FE48: guard word
// data_007266C0, object data_007266C4 (4 bytes, vtable ro_006F6500).
struct TypeInfoRoot {
    TypeInfoRoot();
    virtual bool isDerived(const void* t) const;
};

// ---------------------------------------------------------------------------
// Hookshot itself.  Own members start at 0x40C (ActorBase is 0x40C bytes).
// ---------------------------------------------------------------------------
class Hookshot : public ActorBase {
public:
    Hookshot(ActorParam* p);
    virtual ~Hookshot();
    virtual void v19();            // vtable offset 0x4C (ro_6CD7E4[19])
    virtual void v20();            // vtable offset 0x50 (ro_6CD7E4[20])

    // The eight state handlers, in the order ro_6A16B8 lists them.
    void st0Enter(); void st0Exec(); void st0Exit();
    void st1Enter(); void st1Exec(); void st1Exit();
    void st2Enter(); void st2Exec(); void st2Exit();
    void st3Enter(); void st3Exec(); void st3Exit();
    void st4Enter(); void st4Exec(); void st4Exit();
    void st5Enter(); void st5Exec(); void st5Exit();
    void st6Enter(); void st6Exec(); void st6Exit();
    void st7Enter(); void st7Exec(); void st7Exit();

    Delegate m40c;                 // 0x40C  {vt ro_6F4554, this, {0x4c,1}}
    Delegate m41c;                 // 0x41C  {vt ro_6F4554, this, {0x50,1}}
    void** m42c;                   // 0x42C  new u32[cnt]      (0x18FD68)
    Sub438** m430;                 // 0x430  new Sub438[cnt]   (0x18FDC0)
    void* m434;                    // 0x434  (0x18FBFC `str r7, [r0, #0x434]!`)
    Sub438 m438;                   // 0x438
    StateMgr mStateMgr;            // 0x49C
    Vec3 m4c0;                     // 0x4C0
    Vec3 m4cc;                     // 0x4CC
    Vec3 m4d8;                     // 0x4D8
    u8 m4e4;                       // 0x4E4  = 0x19
    char pad4e5[3];
    u32 m4e8;                      // 0x4E8  = 0
    Vec3 m4ec;                     // 0x4EC
    f32 m4f8;                      // 0x4F8  = 0.0f
    u32 m4fc;                      // 0x4FC
    char pad500[0x520 - 0x500];
    u32 m520;                      // 0x520
    void* m528;                    // 0x528
    void* m52c;                    // 0x52C
    void* m530;                    // 0x530
    void* m534;                    // 0x534
    Delegate m538;                 // 0x538  {vt ro_6F4554, this, {0x18F62C,0}}
    Delegate m548;                 // 0x548  {vt ro_6F4554, this, {0x18E070,0}}
    u16 m558;                      // 0x558  never written; 2 bytes of padding
    u16 m55a;                      // 0x55A  (0x18FCA0 `strh r7, [fp, #0x5a]`)
    u8 m55c;
    u8 m55d;                       // 0x55D
    u8 m55e;                       // 0x55E  = (param->0x44 % 10) != 0
    u8 m55f;
    u8 m560;                       // 0x560
    u8 m561;                       // 0x561
    u8 m562;                       // 0x562  = 1 when the target actor was found
    u8 m563;
    Vec3 m564;                     // 0x564  = sead::Vector3f::zero (0x7A9260)
    f32 m56c;                      // 0x56C  = zero.z
    char pad570[0x57c - 0x570];
    u32 m57c;                      // 0x57C  = param->0x4C (actor handle)
};

#endif
