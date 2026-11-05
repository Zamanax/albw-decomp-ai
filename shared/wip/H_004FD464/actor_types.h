// actor_types.h -- recovered types for the ALBW enemy actor hierarchy, written for
// 0x004FD464 EnemyBase::EnemyBase(EnemyArg*, EnemyParam*) (2384 bytes, 31 primary
// vtable slots, secondary vptr at +0x320).
//
// Every claim below is backed by the instruction that proves it; addresses in
// parentheses are the instructions of 0x4FD464 unless noted otherwise.
//
// Layout check: sizeof(EnemyBase) == 0x8BC with this header (verified by
// compiling `int f(){return sizeof(EnemyBase);}`), which is exactly where the
// derived constructors put their first member (StateMgr at +0x8BC in 0x206FBC
// and 0x22141C).
//
// Reusable by any other enemy actor constructor: derived ctors call this one as
// `EnemyBase(arg, param)` (e.g. 0x22141C: `EnemyBase(arg, &bss_007467F0)`,
// 0x206FBC: `EnemyBase(arg, &bss_739DF4)`) and then continue with their own
// members at/after +0x8BC (StateMgr at +0x8BC in both of those).

#ifndef ACTOR_TYPES_H
#define ACTOR_TYPES_H

#include "albw_types.h"
#include "vec3.h"

// ---------------------------------------------------------------- operator new
// 0x10BAB4 operator new(u32 size, NoThrowTag): the tag is passed by value in r1,
// which the callee ignores ("r1 = garbage/any reg").  Shape of the call site:
//   mov r1, <param>; mov r0, #size; bl 0x10BAB4; cmp r0, #0; blne <ctor>
// (0x4FD4A0-0x4FD4B4).
// The tag type must be 1 byte and have a user-declared ctor: with a 4-byte tag
// armcc materialises the temporary and spills it to the stack (str r5,[sp] /
// ldr r1,[sp] before every operator new), with an empty tag it passes no r1 at
// all.  Only this shape reproduces the target's plain `mov r1, r5` (0x4FD4A0,
// 0x4FD4C0, 0x4FD4E8, 0x4FD620).
struct NoThrow {
    NoThrow() {}
    u8 pad;
};
void* operator new(u32 size, NoThrow) throw();
#define nt (NoThrow())

// ---------------------------------------------------------------- ActorBase
// Root actor base class.  Proven by 0x001DEA54 Cls::Cls(ActorParam*) (matched):
// size 0x40C, two vptrs (primary at +0, secondary at +0x320), 21 primary slots.
// Its constructor is 0x150E40 (called here at 0x4FD474 with r1 = the EnemyArg*).
class EnemyBase;
struct EnemyArg;
struct ActorParam;
struct Obj2D0 {
    // +0x18 sub-object: passed by pointer to func_0054DD3C/54 (0x4FDC84, 0x4FDCA0)
    //  and to func_0054D89C (0x4FDCBC).  +0x1C8 u32 array indexed by param->m8
    //  (0x4FDBA0-0x4FDBA4, 0x4FDBD8-0x4FDBDC) and stored into EnemyBase+0x4E0.
    char pad0[0x18];
    u8 m18[0x1c8 - 0x18];
    u32 m1c8[1];
};

struct ActorBaseA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ~ActorBaseA();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    virtual void v9();  virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    void func_004ECF6C();
    char pad004[0x2d0 - 4];
    Obj2D0* m2d0;               // 0x2D0: read at 0x4FDB98, 0x4FDBCC, 0x4FDC70, 0x4FDC98
    char pad2d4[0x2e0 - 0x2d4];
    u32 m2e0;
    char pad2e4[0x320 - 0x2e4];
};
struct ActorBaseB {                // secondary base: vptr at +0x320 (0x4FD488)
    virtual void b0();
};

class ActorBase : public ActorBaseA, public ActorBaseB {
public:
    ActorBase(EnemyArg* p);
    virtual ~ActorBase();
    char pad324[0x3a4 - 0x324];
    Obj2D0* m3a4;              // 0x3A4: u16 at +2 feeds EnemyBase+0x50A/0x508 (0x4FDD4C-0x4FDD64)
    char pad3a8[0x3cc - 0x3a8];
    u8 m3cc;                   // 0x3CC: set to 1 by the ctor (0x4FDB3C)
    char pad3cd[0x3ec - 0x3cd];
    void* m3ec;                // 0x3EC: set to &EnemyBase::m554 (0x4FDC60)
    char pad3f0[0x40c - 0x3f0];
};

// ---------------------------------------------------------------- EnemyArg / EnemyParam
// EnemyArg is opaque here: it is only forwarded to ActorBase (0x4FD474).
struct EnemyArg;

// +0x00 flags   : bit0/bit1/bit2 gate the three optional init blocks
//                 (0x4FDB90 tst #1, 0x4FDC2C lsls #0x1e, 0x4FDC68 lsls #0x1d)
// +0x04 u32     : passed to func_0014E428 as `v | 1` (0x4FDBE4)
// +0x08 s32     : index into Obj2D0::m1c8[] (0x4FDB9C, 0x4FDBD0)
// +0x0C s32     : if < 0, func_005330BC(obj, &param->m18) supplies the value (0x4FDBA8-0x4FDBC0)
// +0x10 struct  : passed by address to func_004F9A2C (0x4FDC34); 5 s8 read there
// +0x18 struct  : passed by address to func_005330BC (0x4FDBB8)
// +0x44 u32     : low byte | 4 -> func_004FC798 flag byte (0x4FDC00-0x4FDC08)
struct EnemyParam {
    u32 m0;
    u32 m4;
    s32 m8;
    s32 mC;
    char m10[8];
    char m18[0x2c];
    u32 m44;
};

// ---------------------------------------------------------------- element types
// Small classes whose out-of-line constructors the array-construction helper
// __aeabi_vec_ctor_nocookie_nodtor calls; each ctor disassembled below.

// 12 bytes, ctor 0x4FD414: str 0,[r0]; strb 0xb,[r0,#4]; vstr 1.0f,[r0,#8]
struct E00E {
    u32 m0;
    u8 m4;
    u8 pad[3];
    f32 m8;
    E00E();
    void clear() {            // body-loop form (0x4FDB5C-0x4FDB64)
        m0 = 0;
        m4 = 0xb;
        m8 = 1.0f;
    }
};
// 4 bytes, ctor 0x4FC988: str 0,[r0]
struct H00E {
    u32 v;
    H00E();
};
// 16 bytes, ctor 0x4F7DFC: vstr 0.5f,[r0]; copy sead Vector3f::zero to +4
struct S00E {
    f32 m0;
    Vec3 m4;
    S00E();
};

// ctor 3-arg delegate-ish {vptr, object, PMF}; 16 bytes.
// The PMF constants live in rodata at 0x69512C: eight 8-byte entries
// (0x4F7784, 0x4F6DB4, 0x4F4A68, 0x4F7A60, 0x4F7E8C, 0x4F8254, 0x4F7BB8,
// 0x2E7274) followed by null entries; the ctor uses entry 2 for m554.mFp
// (0x4FDC40 loads 0x69513C) and the null entry at 0x69517C for the other five
// (0x4FD650/0x4FD66C/0x4FD67C/0x4FD690/0x4FD6A4 read base+0x50).
// 0x4FD664/0x4FD670/0x4FD680/0x4FD694 all store the same vtable ro_006F4C98;
// word +4 is 0 (0x4FD644) or `this` (0x4FDC58); +8..+0xB is an 8-byte
// pointer-to-member (ro table at 0x69512C, zero constant at 0x69517C).
struct Dlg;
typedef void (EnemyBase::*DlgFn)();   // targets are EnemyBase member funcs (ro table 0x69512C)
struct Dlg {
    Dlg() {}
    Dlg(void* o, DlgFn f) : mObj(o), mFp(f) {}
    virtual void invoke();
    void* mObj;
    DlgFn mFp;
};

// ---------------------------------------------------------------- sub-objects of EnemyBase
// 0x5A8: sub-object, 0xB0 bytes (0x5A8..0x657).  Proof that these fields share
// one base: the inline insert at 0x4FDCF0 addresses the list as [r6+0x54] and
// the count as [r6+0xa9] with r6 = this+0x5A8; func_004FC798 does the same with
// its r0 ([r0+0xa8] count, i*3 stride => 12-byte element array at +0).
struct Sub5A8 {
    E00E v[7];                 // +0x00 (0x5A8) built by vec_ctor(0x4FD414,0xc,7)
    void* list[7];             // +0x54 (0x5FC) pointer list, capacity 7
    H00E w[7];                 // +0x70 (0x618) vec_ctor(0x4FC988,4,7)
    H00E x[7];                 // +0x8C (0x634) vec_ctor(0x4FC988,4,7)
    u8 c0;                     // +0xA8 (0x650) count used by func_004FC798
    u8 c1;                     // +0xA9 (0x651) count used by the inline insert
    u8 c2;                     // +0xAA
    u8 c3;                     // +0xAB
    u8 m_ac;                   // +0xAC (0x654) = 0xA
    u8 m_ad;                   // +0xAD (0x655) = 0xA
    u8 m_ae;                   // +0xAE
    u8 m_af;                   // +0xAF

    // 0x4FD764-0x4FD790: c0..c3 = 0 then m_ac = m_ad = 0xA, m_ae = m_af = 0
    Sub5A8() : c0(0), c1(0), c2(0), c3(0), m_ac(0xa), m_ad(0xa), m_ae(0), m_af(0) {}

    // 0x4FDCC8-0x4FDD48 (search unrolled by 2, capacity 7)
    void addUnique(void* p) {
        if (c1 >= 7) return;
        for (s32 i = 0; i < c1; ++i)
            if (list[i] == p) return;
        list[c1] = p;
        ++c1;
    }
};
// 0x748: 2 elements of 16 bytes built with __aeabi_vec_ctor(0x4F7DFC, 0x10, 2)
struct Sub748 {
    S00E v[2];
};

// 0x658: 20 x {0, 0, 1.0f} (0x4FD810-0x4FD8A8).  The stores are straight-line
// (str 0, str 0, vstr 1.0f per 12-byte element), so the source is not a loop: the
// element is {u32,u32,f32} (both zeros stored from a GPR) and every element is
// initialised individually.
struct A03E {
    u32 a, b;
    f32 c;
};
struct Sub658 {
    A03E v[20];
    Sub658() {
        v[0].a = 0; v[0].b = 0; v[0].c = 1.0f;
        v[1].a = 0; v[1].b = 0; v[1].c = 1.0f;
        v[2].a = 0; v[2].b = 0; v[2].c = 1.0f;
        v[3].a = 0; v[3].b = 0; v[3].c = 1.0f;
        v[4].a = 0; v[4].b = 0; v[4].c = 1.0f;
        v[5].a = 0; v[5].b = 0; v[5].c = 1.0f;
        v[6].a = 0; v[6].b = 0; v[6].c = 1.0f;
        v[7].a = 0; v[7].b = 0; v[7].c = 1.0f;
        v[8].a = 0; v[8].b = 0; v[8].c = 1.0f;
        v[9].a = 0; v[9].b = 0; v[9].c = 1.0f;
        v[10].a = 0; v[10].b = 0; v[10].c = 1.0f;
        v[11].a = 0; v[11].b = 0; v[11].c = 1.0f;
        v[12].a = 0; v[12].b = 0; v[12].c = 1.0f;
        v[13].a = 0; v[13].b = 0; v[13].c = 1.0f;
        v[14].a = 0; v[14].b = 0; v[14].c = 1.0f;
        v[15].a = 0; v[15].b = 0; v[15].c = 1.0f;
        v[16].a = 0; v[16].b = 0; v[16].c = 1.0f;
        v[17].a = 0; v[17].b = 0; v[17].c = 1.0f;
        v[18].a = 0; v[18].b = 0; v[18].c = 1.0f;
        v[19].a = 0; v[19].b = 0; v[19].c = 1.0f;
    }
};
// ---------------------------------------------------------------- heap members
// Each is `new (nt) T(...)` behind operator new 0x10BAB4.
struct X00E {                 // size 0x64, ctor 0x4EE484() (0x4FD4B4; r1 keeps the new tag)
    u8 pad[0x64];
    X00E();
};
struct X10E {                 // size 0x0C, ctor 0x32493C() (0x4FD4E0)
    u8 pad[0xc];
    X10E();
};
struct X20E {                 // size 0x48, ctor 0x34CAA0() (0x4FD4F8, in-place at 0x4FD944)
    u8 pad[0x48];
    X20E();
};
class EnemyBase;
struct X30E {                 // size 0x2C4, ctor 0x2B2590(this) (0x4FD638)
    u8 pad[0x2c4];
    X30E(EnemyBase* owner);
};



// ---------------------------------------------------------------- EnemyBase
// Flag tests: the three optional blocks are gated on bits 0/1/2 of
// EnemyParam::m0.  Bit 0 is a plain `tst r0,#1` (0x4FDB90); bits 1 and 2 are
// `lsls r0,r0,#0x1e/#0x1d; bmi` (0x4FDC2C, 0x4FDC68), which armcc only emits
// for a signed shift test, so the source tests `(s32)(m0 << 30) >= 0` and
// `(s32)(m0 << 29) >= 0` (semantically identical to !(m0 & 2) / !(m0 & 4)).
// ctor 0x4FD464, size 0x8BC (derived ctors put their first member there:
// StateMgr at +0x8BC in 0x206FBC and 0x22141C).  Vtables: ro_006EDB00 with 31
// primary slots, {offset-to-top -0x320, typeinfo} at +0x7C, secondary vtable at
// +0x84 (= the value stored at +0x320, 0x4FD484-0x4FD48C).  So EnemyBase adds
// exactly 10 primary slots over ActorBase's 21.
//
// Every offset below is the store target in the constructor; the comment gives
// the instruction that initialises it.
class EnemyBase : public ActorBase {
public:
    EnemyBase(EnemyArg* arg, EnemyParam* param);
    virtual void v31();  virtual void v32();  virtual void v33();  virtual void v34();
    virtual void v35();  virtual void v36();  virtual void v37();  virtual void v38();
    virtual void v39();  virtual void v40();
    // ro_0069512C holds eight 8-byte pointer-to-member constants (0x4F7784,
    // 0x4F6DB4, 0x4F4A68, 0x4F7A60, 0x4F7E8C, 0x4F8254, 0x4F7BB8, 0x2E7274)
    // followed by null entries.  m554.mFp is the 0x4F4A68 constant (0x4FDC40
    // loads 0x69513C); the five null PMFs are the zero constant at 0x69517C
    // (0x4FD650/0x4FD66C/0x4FD67C/0x4FD690/0x4FD6A4 read base+0x50).
    void func_004F7784(); void func_004F6DB4(); void func_004F4A68();
    void func_004F7A60(); void func_004F7E8C(); void func_004F8254();
    void func_004F7BB8(); void func_002E7274();

    u32 m40c;                 // 0x40C = 0 (0x4FD490), then func_0014E428 (0x4FDBFC)
    u32 m410;                 // 0x410 = 0
    u32 m414;                 // 0x414 = 0
    u32 m418;                 // 0x418 = 0
    u32 m41c;                 // 0x41C = 0, then func_0054D89C (0x4FDCC4)
    X00E* m420;               // 0x420 = new X00E (0x64)      stm r1,{r0,fp} at 0x4FD4BC
    u32 m424;                 // 0x424 = 0
    u32 m428;                 // 0x428..0x434 = 0
    u32 m42c;
    u32 m430;
    u32 m434;
    X10E* m438;               // 0x438 = new X10E (0x0C)     (0x4FD4E4)
    X20E* m43c;               // 0x43C = new X20E (0x48)     (0x4FD51C stm {r0,r7,r8,sb})
    Dlg* m440;                // 0x440 = &m524
    Dlg* m444;                // 0x444 = &m534
    Dlg* m448;                // 0x448 = &m544
    Vec3 m44c;                // 0x44C = sead Vector3f::zero (ldm/stm 0x7A9260, 0x4FD538)
    Vec3 m458;                // 0x458 = 0x7A9254             (0x4FD548)
    Vec3 m464;                // 0x464 = zero                 (0x4FD558)
    Vec3 m470;                // 0x470 = 0x7A9254             (0x4FD564)
    Vec3 m47c;                // 0x47C = zero                 (0x4FD574)
    Vec3 m488;                // 0x488 = 0x7A9254             (0x4FD580)
    Vec3 m494;                // 0x494 = zero                 (0x4FD58C)
    Vec3 m4a0;                // 0x4A0 = 0x7A9254             (0x4FD598)
    u32 m4ac;                 // 0x4AC = 0
    u32 m4b0;                 // 0x4B0 = 0
    u8 m4b4;                  // 0x4B4 = 0
    u8 m4b5;                  // 0x4B5 = 0
    u8 pad4b6[2];
    Vec3 m4b8;                // 0x4B8 = zero
    f32 m4c4;                 // 0x4C4 = 1.0f (s17)
    f32 m4c8;                 // 0x4C8 = 1.0f
    f32 m4cc;                 // 0x4CC = 1.0f, set again at 0x4FDB40
    Vec3 m4d0;                // 0x4D0 = zero
    u8 m4dc;                  // 0x4DC = 8
    u8 pad4dd[3];
    u32 m4e0;                 // 0x4E0 = 0, then m2d0->m1c8[param->m8] (0x4FDBE0)
    Vec3 m4e4;                // 0x4E4 = 0x7A9254 (ldm {r0,r2} + ldr [r1,#8])
    f32 m4f0;                 // 0x4F0 = 1.0f
    f32 m4f4;                 // 0x4F4 = 1.0f
    f32 m4f8;                 // 0x4F8 = 1.0f
    u32 m4fc;                 // 0x4FC = 0
    u32 m500;                 // 0x500 = 0
    u32 m504;                 // 0x504 = 0
    u16 m508;                 // 0x508 = 4, then ActorBase::m3a4->m2 (0x4FDD64)
    u16 m50a;                 // 0x50A = 4, then same value (0x4FDD60)
    u16 m50c;                 // 0x50C = 4
    u16 m50e;                 // 0x50E = 4
    X30E* m510;               // 0x510 = new X30E(this) (0x2C4) (0x4FD640)
    Dlg m514;                 // 0x514-0x523 {vtbl ro_006F4C98, 0, null PMF} (0x4FD644-0x4FD664)
    Dlg m524;                 // 0x524  same shape (0x4FD668-0x4FD674)
    Dlg m534;                 // 0x534  same (0x4FD678-0x4FD688)
    Dlg m544;                 // 0x544  same (0x4FD68C-0x4FD698)
    Dlg m554;                 // 0x554  {vtbl, 0, null PMF} (0x4FD69C-0x4FD6B8);
                              //        body sets mObj=this, PMF=0x4F4A68 (0x4FDC58-0x4FDC5C)
    Vec3 m564;                // 0x564 = (0,0,0) as three vstr s16 (0x4FD6BC)
    Vec3 m570;                // 0x570 = (0,0,0) as three vstr s16 (0x4FD6D0)
    f32 m57c;                 // 0x57C = 0.0f (vstr s16, 0x4FD6E4)
    f32 m580;                 // 0x580 = 0.0f (vstr s16, 0x4FD6F0)
    u32 m584;                 // 0x584 = 0x1F08  (stm r3,{r0,r1,r2} 0x4FD6F4)
    u32 m588;                 // 0x588 = 0x36
    u32 m58c;                 // 0x58C = 0xDDF
    Vec3 m590;                // 0x590 = zero
    u32 m59c;                 // 0x59C = 0x1F390003 (0x4FD718), |= 0x400 (0x4FDC24)
    u32 m5a0;                 // 0x5A0 = 0x3000
    u32 m5a4;                 // 0x5A4 = m5a0 read back (0x4FD71C)
    Sub5A8 m5a8;              // 0x5A8..0x657 (see Sub5A8)
    Sub658 m658;              // 0x658: 20 x {0,0,1.0f} (0x4FD810-0x4FD8A8)
    Sub748 m748;              // 0x748: vec_ctor(0x4F7DFC,0x10,2) at 0x4FD8C0
    u8 m768;                  // 0x768 = 0
    u8 pad769[3];
    u8 m76c;                  // 0x76C = 0
    u8 pad76d[3];
    Vec3 m770;                // 0x770 = zero
    u8 m77c;                  // 0x77C = 1
    s8 m77d;                  // 0x77D = -1
    s8 m77e;                  // 0x77E = -1
    u8 m77f;                  // 0x77F = 0
    s8 m780;                  // 0x780 = -1
    u8 pad781[1];
    u16 m782;                 // 0x782 = 0x5A
    u16 m784;                 // 0x784 = 0
    u16 m786;                 // 0x786 = -1 (0xFFFF)
    u16 m788;                 // 0x788 = -1 (0xFFFF)
    u8 pad78a[0xe];
    f32 m798;                 // 0x798 = 1.2f (0x3F99999A)
    u32 m79c;                 // 0x79C = 0
    u32 m7a0;                 // 0x7A0 = 0
    u32 m7a4;                 // 0x7A4 = 0
    Vec3 m7a8;                // 0x7A8 = zero
    X20E m7b4;                // 0x7B4: in-place ctor 0x34CAA0 (0x4FD944)
    u8 m7fc;                  // 0x7FC = 0 (after the ctor, 0x4FD94C)
    u8 pad7fd[3];
    u32 m800;                 // 0x800..0x820 = 0
    u32 m804;
    u32 m808;
    u32 m80c;
    u32 m810;
    u32 m814;
    u32 m818;
    u32 m81c;
    u32 m820;
    u8 m824;                  // 0x824..0x827 = 0xFF
    u8 m825;
    u8 m826;
    u8 m827;
    u8 m828;                  // 0x828..0x82A = 0
    u8 m829;
    u8 m82a;
    u8 pad82b[1];
    Vec3 m82c;                // 0x82C = zero
    u16 m838;                 // 0x838 = 0
    u8 pad83a[2];
    Vec3 m83c;                // 0x83C = zero
    u8 m848;                  // 0x848..0x84A = 0
    u8 m849;
    u8 m84a;
    u8 pad84b[1];
    f32 m84c;                 // 0x84C = 0.0f
    u8 m850;                  // 0x850 = 2
    u8 m851;                  // 0x851 = data_0070A5A4 byte, then func_004FA000(0)[0]
    u8 m852;                  // 0x852 = 0
    u8 m853;                  // 0x853 = 0
    f32 m854;                 // 0x854 = 0.0f
    u8 m858;                  // 0x858 = 1
    u8 m859;                  // 0x859 = 0
    u8 m85a;                  // 0x85A = 0
    u8 m85b;                  // 0x85B = 0
    u32 m85c;                 // 0x85C = 0
    u32 m860;                 // 0x860 = 0
    f32 m864;                 // 0x864 = 1.0f
    u32 m868;                 // 0x868 = 0
    u32 m86c;                 // 0x86C = 0
    f32 m870;                 // 0x870 = 1.0f
    u8 m874;                  // 0x874..0x877 = 0x80
    u8 m875;
    u8 m876;
    u8 m877;
    u32 m878;                 // 0x878 = data_0070A5AC
    u8 m87c;                  // 0x87C = 0xA
    u8 m87d;                  // 0x87D = 0x14
    u8 m87e;                  // 0x87E = 0x28
    u8 m87f;                  // 0x87F = 0xA
    u8 m880;                  // 0x880 = 0xF
    u8 m881;                  // 0x881 = 5
    u8 m882;                  // 0x882 = 0
    u8 pad883[1];
    void* m884;               // 0x884 = &m884 (self, 0x4FDAC8)
    void* m888;               // 0x888 = &m884 (0x4FDAC0)
    u32 m88c;                 // 0x88C = 0
    u32 m890;                 // 0x890 = 0x28 (0x4FDB1C)
    u8 m894;                  // 0x894 = 0
    u8 m895;                  // 0x895 = 0
    u8 m896;                  // 0x896 = 1
    u8 m897;                  // 0x897 = 0
    f32 m898;                 // 0x898 = 0.0f
    u8 m89c;                  // 0x89C..0x89F = 0
    u8 m89d;
    u8 m89e;
    u8 m89f;
    u32 m8a0;                 // 0x8A0 = 0
    u32 m8a4;                 // 0x8A4 = 0
    Vec3 m8a8;                // 0x8A8 = zero
    u8 m8b4;                  // 0x8B4 = 0
    u8 m8b5;                  // 0x8B5 = 0, 1 when data_00709DF8->m18 == 0x14 (0x4FDD80)
    u8 m8b6;                  // 0x8B6 = 0
    u8 m8b7;                  // 0x8B7 = 1
    u8 m8b8;                  // 0x8B8 = 0, 1 when data_00709DF8->m18 == 0x0B (0x4FDD8C)
    u8 pad8b9[3];             // size 0x8BC
};

#endif  // ACTOR_TYPES_H
