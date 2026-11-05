// Types recovered from En206::En206 at 0x00206FBC (2268 B, vtable ro_6D2764, secondary vtable at
// +0x320 = primary + 0x84, StateMgr at +0x8BC, object size 0x9A4 -- func_006047B8 does
// `new S(2468)` with S's ctor = 0x00206FBC).
//
// Every claim below is backed by the instruction address that shows it (addresses are relative to
// the game image; the target function occupies 0x00206FBC..0x00207894).
//
// ---------------------------------------------------------------------------------------------
// 1. EnemyBase: the shared actor base, 0x8BC bytes, ctor 0x4FD464(EnemyArg*, EnemyParam*)
//    - primary vtable written by its ctor: ro_006EDB00 at +0 (`str r1,[r4]`, 0x4FD48C)
//    - secondary base at +0x320, vtable = primary + 0x84 (0x4FD484 `add r0,r1,#0x84`)
//    - the derived ctor immediately re-writes both with its own vtable (0x206FD8/0x206FE0), which
//      is why the derived class's primary vtable must have exactly 33 slots (0x84/4).  With
//      armcc, `29` virtual functions in the primary base + 2 in the derived class (plus the 2
//      secondary-base/ordering extras) give 33 -- i.e. `add r1,r2,#0x84` appears exactly when the
//      derived class declares two more virtuals than PrimBase (verified: 27 virtuals -> #0x7c,
//      28 -> #0x80, 29 -> #0x84).
//    - the third argument of the base ctor is the per-class parameter block bss_00739DF4
//      (0x206FC4 `ldr r2,[pc]` before the call), so the signature is (EnemyArg*, EnemyParam*).
//
// 2. En206 layout (all offsets the ctor touches):
//      0x000 primary vtable, 0x320 secondary vtable           (0x206FD8/0x206FE0)
//      0x054 u16                              (0x207798 ldrh -> Model+0x2c at 0x2077A0)
//      0x2CC u32                              (0x20777C -> func_004EDAD0's id argument)
//      0x2D7 u8                               (0x2070F0 strblt = 1 when player y < 10.0f)
//      0x3D0 Vec3                             (0x207754 12-byte ldm copied to Obj4+4)
//      0x3EC void* = &m8E0                    (0x2070FC)
//      0x448 void* = &m994                    (0x2077B8)
//      0x468 f32 = 0.5f                       (0x207720 vstr s0,[r1,#0x68])
//      0x77D/0x77E/0x77F u8 = 0/0xFF/0         (0x20773C-0x20774C)
//      0x853 u8 = 1                           (0x207724)
//      0x8BC StateMgrT<En206>  (0x24 bytes)   (0x206FE4 `bl 0x10A794` with this = +0x8BC)
//      0x8E0 delegate record (16 bytes)       (0x206FF0..0x20701C)
//      0x8F0 12 bytes, never written by this ctor
//      0x8FC..0x938 scalars, 0x928/0x934 = 1.0f  (0x207024..0x207080)
//      0x93C Vec3 = sead::Vector3f::zero (data_007A9260)  (0x207084 ldm/stm, 0x20706C pool)
//      0x948 Obj4* = Actor::getObj(0)         (0x20709C `bl 0x54D964`, 0x2070A0)
//      0x94C Model (0x48 bytes, ctor 0x4EDC9C, 0x2070AC)
//      0x994 delegate record (16 bytes)       (0x2070BC..0x2070C8)
//    Object size 0x9A4.
//
// ---------------------------------------------------------------------------------------------
// 3. StateMgr.  StateMgrBase's own out-of-line ctor 0x10A794 writes, and nothing else:
//      +0x00 u32 mCounter   (0x10A79C)
//      +0x04 s8  mCur = -1  (0x10A7A0)
//      +0x05 s8  mNext = -1 (0x10A7A4)
//      +0x06 u8  mNum = 0   (0x10A7A8)
//      +0x08 u32 mNumNames  (0x10A7AC)
//      +0x0c FixedSafeString<24>* mNames (0x10A7B0)
//      +0x10 void* mTimeline (0x10A7B4)
//    so StateMgrBase is 0x14 bytes and the derived template adds mOwner/mEnter/mExec/mExit, which
//    its *inlined* constructor zeroes in this order (0x206FEC, 0x206FF4, 0x206FF8, 0x206FFC).
//    * StateMgrBase::setStateName(s32 idx, const SafeString&) = 0x10BEC4.  It indexes mNames with
//      a stride of 0x24 (0x10BED8 `addhi r0,r1,r1,lsl#3` + `addhi r6,r6,r0,lsl#2`), so the name
//      buffer holds sead::FixedSafeString<24> objects.  (This corrects statemgr.h's
//      `u32 mNames[2]`: the two words at +0x08/+0x0C are a sead Buffer {count, pointer}.)
//    * changeState is out of line once per actor class; En206 calls 0x65D4EC.
//
// 4. The name buffer is built by the ctor itself (0x207220..0x2072D8):
//      operator new[](size, heap=0, align=4)           0x20729C `bl 0x10CEE0`  (r0 = 8 + n*0x24)
//      array cookie {0x24, n} stored at base           0x2072B4/0x2072B8 (`mov r1,#0x24; stm r5,{r1,r8}`)
//      __aeabi_vec_ctor_nocookie_nodtor(base+8, 0x10BDF0, 0x24, n)   0x2072C8
//      mNames = base+8; mNumNames = n                  0x2072D0/0x2072D4
//    The cookie only appears because the element class has a *non-trivial destructor* (a virtual
//    destructor in sead::SafeString).  A temporary SafeString with an inline-empty virtual dtor,
//    on the other hand, must NOT produce a destructor call at the setStateName call sites.
//
// 5. The per-class state table is a single source-level rodata object at ro_00695BF0, 0xE4 bytes:
//        +0x00 f32 mRate = 1.0f
//        +0x04 mFuncs[28]  (8-byte pointer-to-member constants, 4-byte aligned)
//    The 28 entries, value by value (verified by dumping the image at 0x695BF0):
//        0 0x2069FC (delegate cb at +0x8E0)   1 0x206D28 (delegate cb at +0x994)
//        2 0x205F1C state0 enter   3 0x206E20 state0 exec   4 0 (null, used for every mExit)
//        5 0x20658C  6 0x2063D8   (state1)     7 0x205F48  8 0x206E44  (state2)
//        9 0x205DFC 10 0x206D90  (state3)    11 0x2063FC 12 0x206018  (state4)
//       13 0x205DF4 14 0x206D18  (state5)    15 0x20673C 16 0x20661C  (state6)
//       17 0x2066CC 18 0x20659C  (state7)    19 0x206718 20 0x2065C8  (state8)
//       21 0x2068A8 22 0x20664C  (state9)    23 0x205E38 24 0x206DB8  (state10)
//       25 0x20643C 26 0x2060E8  (state11)   27 0 (null, used for the enter/exec fill)
//    The block ends at 0x695CD4 (the next object of the unit starts there with 1.1f), and the
//    static initialiser 0x5BA5DC passes its address as a registration parameter, so it is a
//    source-level table, not a compiler constant pool.  Reading it through `&sTable` loads the
//    base once (`ldr sb,=...` at 0x206FF0) and then uses ldr/ldrd/vldmia with offsets 4+8k.
//
// 6. State machine construction recipe (12 states), exactly as the target does it:
//      mState.mNum = 12;  mState.mOwner = this;                0x2071C8/0x2071D4
//      mState.mEnter = new Func[24];                           0x2071D0/0x2071DC  (0xC0 bytes)
//      mState.mExec  = mState.mEnter + mState.mNum;            0x2071E0/0x2071E8  (mNum reloaded)
//      for (i < 24) mEnter[i] = table[27];                     0x2071EC..0x207218 (unrolled x2)
//      mState.mExit = new Func[12];                            0x207220/0x20722C  (0x60 bytes)
//      none = table[4]; for (i < 12) mExit[i] = none;          0x207234..0x20727C (unrolled x2)
//      names buffer (see 4), then per state k, in this order:
//          mState.setStateName(k, "cState_...");               0x2072E4..0x2076C0
//          mEnter[k] = table[e]; mExec[k] = table[e+1]; mExit[k] = none;
//    The name strings in the order they are used: cState_Wait, cState_Kyorokyoro, cState_Walk,
//    cState_Stop, cState_Reaction, cState_Die, cState_PetrificationStart,
//    cState_PetrificationStop, cState_PetrificationShake, cState_PetrificationReveive,
//    cState_Turn, cState_UniqueDie (note the literal misspelling "Reveive").
//    Two function-pointer locals per state (`En206Func e = table[e]; En206Func x = table[x];`
//    then `mEnter[k] = e; mExec[k] = x;`) is what reproduces the target's 16-byte `vldmia`
//    load of the two adjacent table entries followed by two `vstmia` stores; assigning the table
//    elements directly makes armcc emit ldr/ldr/stm instead.
//
// 7. After the state machine (0x2076E8..0x2077B8):
//      if (arg->m2a) { m914 = 0x32; func_004F88A0(this, m91C); changeState(7); }
//      else            changeState(1);
//      m468 = 0.5f; m853 = 1; func_002B1FB4(this, -1, 0x80);
//      m77d = 0; m77e = 0xFF; m77f = 0;
//      m948->m4 = m3d0;                 (12-byte ldm/stm)
//      m948->m28 = 0xA4;                (the value is also spilled to a local first, 0x207768)
//      m94C.m18 = m948;                 (0x207778 str r0,[r4,#0x964])
//      u32 id = m2cc; func_004EDAD0(&m94C, &id);   (the id is passed *by pointer* through a local)
//      m94C.m2c = m54; func_004A7F00(data_00709D28, &m94C, 2);
//      m94C.m44 = 0; m448 = &m994;

#ifndef EN206_ACTOR_TYPES_H
#define EN206_ACTOR_TYPES_H

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

#include "vec3.h"

// ------------------------------------------------------------------ sead strings
namespace sead {
// 8 bytes: vptr (ro_6F5988) + text pointer.  Built on the stack before every setStateName call
// (0x2072F0 stores the text, 0x207300 the vtable).  The virtual destructor must be inline-empty:
// it makes FixedSafeString<24> non-trivial (the array cookie at 0x2072B8) without emitting a
// destructor call for the temporary.
class SafeString {
public:
    SafeString() : mStringTop(0) {}
    SafeString(const char* s) : mStringTop(s) {}
    virtual ~SafeString() {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;   // +0x04
};
}  // namespace sead

// sead::FixedSafeString<24>: 0x24 bytes (element size in the array-new cookie at 0x2072B4,
// stride 0x24 in setStateName 0x10BEDC, ctor 0x10BDF0).
class FixedSafeString24 : public sead::SafeString {
public:
    FixedSafeString24();
    virtual ~FixedSafeString24();
    s32 mBufferSize;   // +0x08
    char mBuf[24];     // +0x0c
};

// ------------------------------------------------------------------ StateMgr
struct StateMgrBase {
    u32 mCounter;               // +0x00
    s8 mCur;                    // +0x04
    s8 mNext;                   // +0x05
    u8 mNum;                    // +0x06
    u8 pad7;                    // +0x07
    u32 mNumNames;              // +0x08  (a sead Buffer: count)
    FixedSafeString24* mNames;  // +0x0c  (a sead Buffer: pointer)
    void* mTimeline;            // +0x10
    StateMgrBase();                                            // 0x10A794
    void setStateName(s32 idx, const sead::SafeString& name);   // 0x10BEC4
};

template <class T>
struct StateMgrT : StateMgrBase {
    typedef void (T::*Func)();
    T* mOwner;     // +0x14
    Func* mEnter;  // +0x18
    Func* mExec;   // +0x1c
    Func* mExit;   // +0x20
    StateMgrT() : mOwner(0), mEnter(0), mExec(0), mExit(0) {}   // inlined: 4 zero stores
    void changeState(s32 s);   // En206: 0x65D4EC
};

// ------------------------------------------------------------------ actor base
// 0x320-byte primary base; only the virtual count matters for the code (33 slots in the vtable of
// the derived actor -> secondary vtable = primary + 0x84).
struct PrimBase {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    char pad[0x54 - 4];
    u16 m54;         // 0x207798
    char pad2[0x2cc - 0x56];
    u32 m2cc;        // 0x20777C
    char pad3[0x2d7 - 0x2d0];
    u8 m2d7;         // 0x2070F0
    char pad4[0x320 - 0x2d8];
};
struct SecBase { virtual void s0(); };

struct EnemyParam { char pad[0x200]; };          // per-class parameter block, bss_00739DF4
struct EnemyArg { char p0[0x2a]; u16 m2a; u16 m2c; char p2e[0x40]; };   // 0x2076E8 / 0x2070CC

struct EnemyBase : PrimBase, SecBase {
    EnemyBase(EnemyArg* arg, EnemyParam* param);   // 0x4FD464
    char p324[0x3d0 - 0x324];
    Vec3 m3d0;
    char p3dc[0x3ec - 0x3dc];
    void* m3ec;
    char p3f0[0x448 - 0x3f0];
    void* m448;
    char p44c[0x468 - 0x44c];
    f32 m468;
    char p46c[0x77d - 0x46c];
    u8 m77d, m77e, m77f;
    char p780[0x853 - 0x780];
    u8 m853;
    char p854[0x8bc - 0x854];
};

// ------------------------------------------------------------------ member types
// A 16-byte callback record {per-class rodata record, owner, pointer-to-member}.  Both instances in
// En206 point at ro_006F4758 (a per-class rodata record whose first word is the code address
// 0x68405C; the record is 12 bytes {fn, 0, 0} and the only code reference to it is this ctor).
extern char ro_006F4758[];

struct En206;
typedef void (En206::*En206Func)();

struct Delegate16 {
    void* mInfo;            // +0x00
    En206* mObj;            // +0x04
    En206Func mFunc;        // +0x08  (8-byte PMF constant from the state table)
    Delegate16(void* i, En206* o, En206Func f) : mInfo(i), mObj(o), mFunc(f) {}
};

// 0x48-byte bcl model holder (ctor 0x4EDC9C).  Offsets from the code that touches it:
//   +0x18 Obj4* (0x207778), +0x20 u32 id (func_004EDAD0 0x4EDADC), +0x28 callback,
//   +0x2c u16 actor id (0x20776C), +0x44 u8 visible (0x2077B4).
struct Model48 {
    Model48();
    u8 pad[0x10];
    void* m10;
    void* m14;
    void* m18;
    u8 pad1c[4];
    u32 m20;
    u8 pad24[4];
    void* m28;
    u16 m2c;
    u8 pad2e[0x44 - 0x2e];
    u8 m44;
    u8 pad45[0x48 - 0x45];
};

// Actor::getObj(0) result (0x54D964): its position is a Vec3 at +0x04 (0x20775C stm), and the
// model id is a u16 at +0x28 (0x20776C).
struct Obj4 {
    u8 pad[4];
    Vec3 m4;
    u8 p10[0x28 - 0x10];
    u16 m28;
};

// The per-class state table (see 5 above).
struct StateTable {
    f32 mRate;                 // +0x00 = 1.0f
    En206Func mFuncs[28];      // +0x04
};

#endif
