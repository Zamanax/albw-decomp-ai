// Actor framework: the root actor class and the polymorphic actor hierarchy.
//
// The game's root actor is a 0x40C-byte object with two polymorphic bases: the primary one at
// +0x000 (21 virtual slots) and a secondary one at +0x320.  Matched sources call them
// ActorBaseA/ActorBaseB (56 files), A/B (1 file), Primary/Secondary (3 files), ABaseA/ABaseB
// (1 file); the layout is identical and the naming difference is handled by headermigrate
// --rename, not by duplicate types.
//
// Evidence:
//   0x150E40  ActorBase::ActorBase(ActorParam*)      ctor, 0x40C bytes; run at 0x1DEA54 (Player)
//   0x4ED00C  ActorBaseA::ActorBaseA()               primary base ctor
//   0x1DF43C  Player::~Player                        21 primary slots, secondary vptr at +0x5c,
//                                                    i.e. the primary vtable has (0x5c-8)/4 = 21 slots
//   0x1DEA54  Cls::Cls(ActorParam*)                  Cls's first own member at +0x40C
//   0x4FD464  EnemyBase::EnemyBase(EnemyArg*, EnemyParam*)  secondary vptr at +0x320, size 0x8BC
//
// Offsets below are the store targets of the constructors that initialise them; each comment
// carries the instruction address that proves it.  Uncalled inline members generate no code, so
// the member set is a superset of what any single matched source used.

#ifndef ACTOR_H
#define ACTOR_H

#include "albw_types.h"
#include "vec3.h"

struct ActorParam;

// Object reachable through ActorBaseA::m2d0 (+0x2d0) and ActorBaseB::m3a4 (+0x3a4).
// Only ever used behind a pointer; the +0x18 sub-object is passed to func_0054DD3C/54/8C
// (0x4FDC84, 0x4FDCA0, 0x4FDCBC) and its +0x1c8 array is indexed by ActorParam-like ids
// (0x4FDBA0, 0x4FDBD8).  Files that define it keep their own definition.
struct Obj2D0;

// ---------------------------------------------------------------------------------------------
// Primary base: +0x000..0x320.
//
// The 21 slots: v0..v2, ~ActorBaseA, then v5..v20 (the numbering gap is how the matched sources
// spell it; the slot count is what the secondary vtable offset at +0x5c proves).
// ---------------------------------------------------------------------------------------------
struct ActorBaseA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ~ActorBaseA();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    virtual void v9();  virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();

    void func_004ECF6C();      // 0x4ECF6C virtual-slot helper used by the ctor
    u8 pad004[0x54 - 4];
    s16 m54;                   // +0x054  (0x1904FC ldrsh r0,[r4,#0x54]; 0x2CCF98 ldrh)
    u8 pad056[0x2cc - 0x056];
    u32 m2cc;                  // +0x2CC  (0x190448 ldr r0,[r4,#0x2cc]; 0x2CCF80)
    Obj2D0* m2d0;              // +0x2D0  (0x4FDB98, 0x1901B0, 0x18FE60 dyn-cast target)
    u8 pad2d4[0x2d7 - 0x2d4];
    u8 m2d7;                   // +0x2D7  (0x18FE78 strbeq r0,[r4,#0x2d7])
    u8 pad2d8[0x2e0 - 0x2d8];
    u32 m2e0;                  // +0x2E0  (0x1901B8 area; word read by the state setup)
    u8 pad2e4[0x320 - 0x2e4];
};

// ---------------------------------------------------------------------------------------------
// Secondary base: +0x320..0x40C (0xEC bytes).  54 matched sources spell its extent as
// `char padB[0x410 - 0x324]` after the vptr, which is exactly 0x40C - 0x320 = 0xEC.
// ---------------------------------------------------------------------------------------------
struct ActorBaseB {
    virtual void b0();

    u8 pad324[0x354 - 0x324];
    void* m354;                // +0x354  = &stateMgr (0x1901B8; 0x2CCB64 str r0,[r4,#0x354])
    u8 pad358[2];
    u16 m35a;                  // +0x35A  = 11 (0x1901C0 strh r1,[r2,r4]; 0x2CCB74)
    u8 pad35c[0x3a0 - 0x35c];
    u32 m3a0;                  // +0x3A0  (0x1904B0)
    u32 m3a4;                  // +0x3A4  actor/sub-object handle passed to func_004F88A0
                               //         (0x1904B4; 0x4FDD4C reads a u16 at +2)
    u8 pad3a8[0x3cc - 0x3a8];
    u8 m3cc;                   // +0x3CC  = 1 (0x4FDB3C)
    u8 pad3cd[0x3d0 - 0x3cd];
    Vec3 m3d0;                 // +0x3D0  (0x18FEC8 add r0,r4,#0x3d0; 0x18FF60 stores a Vec3)
    f32 m3dc;                  // +0x3DC  (0x190738)
    f32 m3e0;                  // +0x3E0  (0x19073C)
    f32 m3e4;                  // +0x3E4  (0x190740)
    u32 m3e8;                  // +0x3E8  (0x1904B0 area; 0x18FEA8 ldr r2,[r4,#0x3e8])
    void* m3ec;                // +0x3EC  = &EnemyBase::m554 (0x4FDC60)
    u8 pad3f0[0x40c - 0x3f0];
};

// ---------------------------------------------------------------------------------------------
// The root actor.  Two polymorphic bases; sizeof == 0x40C.
// ---------------------------------------------------------------------------------------------
class ActorBase : public ActorBaseA, public ActorBaseB {
public:
    ActorBase(ActorParam* p);   // 0x150E40
    virtual ~ActorBase();
};

// ---------------------------------------------------------------------------------------------
// The enemy-actor family's sources model the class above the root as part of the root itself:
// their first own member sits at +0x410, not at +0x40C.  Proof from the game's own bytes:
// 0x13BBC0 (ActD::~ActD) destroys MemP at this+0x864 = 0x410 + 0x68 (MemZ) + 0x2e4 (MemY)
// + 0x54 (MemX) + 0xb4, and the same dtor destroys MemZ at this+0x410.
// The 4 bytes at +0x40C are the first field of EnemyBase (0x4FD490 `str fp,[r4,#0x40c]`), so this
// class is that prefix: the root plus the actor handle word.  Sources in that family reach it with
// headermigrate --rename 'ActorBase' -> 'ActorBaseExt'.
class ActorBaseExt : public ActorBase {
public:
    u32 m40c;                   // +0x40C  actor handle (EnemyBase::m40c, 0x4FDBFC func_0014E428)
};

// ---------------------------------------------------------------------------------------------
// NpcBase<T>: the npc actor base (ctor 0x623368, which runs the 0x4C18E0 grand-parent ctor, then
// installs the two vtables of vtable pair ro_006CB858/ro_006CB858+0xb8, constructs the state
// machine at +0x960 and stores the initial state at +0x984).
//
// The 252 matched sources that use an npc spell it `Npc` with a partial layout; the union of their
// members is below.  Offsets are absolute in the actor object, as the partial layouts spell them.
// The vtable has 44 slots: v0..v42 and `request` at offset 0xac (0x60B8A8, 0x60BD64).  Sources
// that spell the npc without virtual slots (plain pad arrays) generate the same access offsets,
// and `NpcPlain` is the vtable-less spelling for anything that must not carry one.
// The state machine at +0x960 is left as raw space because its Func tables are member pointers of
// the concrete actor class; `m964` is its mCur byte and `m984` the saved initial state.
struct Child;
struct Obj7ac;
struct M7c0;

struct Npc {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42();

    virtual void request(u8, s32);   // slot 43 (vtable offset 0xac, 0x60BD64)
    u8 pad004[0x2cc - 0x004];
    u32 m2cc;                // +0x2CC
    u8 pad2d0[0x2d7 - 0x2d0];
    u8 m2d7;                 // +0x2D7
    u8 pad2d8[0x3ac - 0x2d8];
    u32 m3ac;                // +0x3AC
    u8 pad3b0[0x3d0 - 0x3b0];
    Vec3 m3d0;               // +0x3D0
    u8 pad3dc[0x3e8 - 0x3dc];
    s32 m3e8;                // +0x3E8
    u8 pad3ec[0x770 - 0x3ec];
    Child* m770;             // +0x770
    u8 pad774[0x7ac - 0x774];
    Obj7ac* m7ac;            // +0x7AC
    u8 pad7b0[0x7c0 - 0x7b0];
    M7c0* m7c0;              // +0x7C0
    u8 pad7c4[0x810 - 0x7c4];
    u32 m810;                // +0x810
    u8 pad814[0x818 - 0x814];
    u32 m818;                // +0x818
    u8 pad81c[0x834 - 0x81c];
    f32 m834;                // +0x834
    u8 pad838[0x848 - 0x838];
    u16 m848;                // +0x848
    u16 m84a;                // +0x84A
    u8 pad84c[0x850 - 0x84c];
    u16 m850;                // +0x850
    u8 m852;                 // +0x852
    u8 m853;                 // +0x853
    u8 m854;                 // +0x854
    u8 pad855[0x857 - 0x855];
    u8 m857;                 // +0x857
    u8 m858;                 // +0x858
    u8 pad859;
    u8 m85a;                 // +0x85A
    s8 m85b;                 // +0x85B
    s8 m85c;                 // +0x85C
    u8 m85d;                 // +0x85D
    u8 m85e;                 // +0x85E
    u8 gate85f;              // +0x85F
    u8 pad860[0x86c - 0x860];
    u32 m86c;                // +0x86C
    u8 pad870[0x8ac - 0x870];
    u32 m8ac;                // +0x8AC
    u8 pad8b0[0x8b4 - 0x8b0];
    f32 m8b4;                // +0x8B4
    f32 m8b8;                // +0x8B8
    u8 pad8bc[0x904 - 0x8bc];
    s16 m904[6];             // +0x904
    u8 pad910[0x911 - 0x910];
    u8 m911;                 // +0x911
    u8 pad912[0x914 - 0x912];
    s8 m914;                 // +0x914
    u8 pad915[0x960 - 0x915];
    u8 pad960[0x964 - 0x960]; // +0x960 StateMgrT<T> (0x24 bytes; its Func tables are member
                              //        pointers of the concrete class, so it stays raw here)
    u8 m964;                 // +0x964  StateMgr::mCur
    u8 pad965[0x984 - 0x965];
    s32 m984;                // +0x984  saved initial state
    u8 m988;                 // +0x988

    void changeState(s32 state, s32 flag);
};

// The same object seen through its vtable: 44 slots (v0..v42 then request at offset 0xac, as
// 0x60B8A8 and 0x60BD64 call it).  Sources that declare the npc's virtual slots use this class;
// the member layout is identical, only the first pad starts after the vptr.
struct NpcPlain {
    void request(u8, s32);   // non-virtual slot of the npc class (see the 43-virtual sources)

    u8 pad000[0x2cc - 0x000];
    u32 m2cc;                // +0x2CC
    u8 pad2d0[0x2d7 - 0x2d0];
    u8 m2d7;                 // +0x2D7
    u8 pad2d8[0x3ac - 0x2d8];
    u32 m3ac;                // +0x3AC
    u8 pad3b0[0x3d0 - 0x3b0];
    Vec3 m3d0;               // +0x3D0
    u8 pad3dc[0x3e8 - 0x3dc];
    s32 m3e8;                // +0x3E8
    u8 pad3ec[0x770 - 0x3ec];
    Child* m770;             // +0x770
    u8 pad774[0x7ac - 0x774];
    Obj7ac* m7ac;            // +0x7AC
    u8 pad7b0[0x7c0 - 0x7b0];
    M7c0* m7c0;              // +0x7C0
    u8 pad7c4[0x810 - 0x7c4];
    u32 m810;                // +0x810
    u8 pad814[0x818 - 0x814];
    u32 m818;                // +0x818
    u8 pad81c[0x834 - 0x81c];
    f32 m834;                // +0x834
    u8 pad838[0x848 - 0x838];
    u16 m848;                // +0x848
    u16 m84a;                // +0x84A
    u8 pad84c[0x850 - 0x84c];
    u16 m850;                // +0x850
    u8 m852;                 // +0x852
    u8 m853;                 // +0x853
    u8 m854;                 // +0x854
    u8 pad855[0x857 - 0x855];
    u8 m857;                 // +0x857
    u8 m858;                 // +0x858
    u8 pad859;
    u8 m85a;                 // +0x85A
    s8 m85b;                 // +0x85B
    s8 m85c;                 // +0x85C
    u8 m85d;                 // +0x85D
    u8 m85e;                 // +0x85E
    u8 gate85f;              // +0x85F
    u8 pad860[0x86c - 0x860];
    u32 m86c;                // +0x86C
    u8 pad870[0x8ac - 0x870];
    u32 m8ac;                // +0x8AC
    u8 pad8b0[0x8b4 - 0x8b0];
    f32 m8b4;                // +0x8B4
    f32 m8b8;                // +0x8B8
    u8 pad8bc[0x904 - 0x8bc];
    s16 m904[6];             // +0x904
    u8 pad910[0x911 - 0x910];
    u8 m911;                 // +0x911
    u8 pad912[0x914 - 0x912];
    s8 m914;                 // +0x914
    u8 pad915[0x960 - 0x915];
    u8 pad960[0x964 - 0x960]; // +0x960 StateMgrT<T> (0x24 bytes; its Func tables are member
                              //        pointers of the concrete class, so it stays raw here)
    u8 m964;                 // +0x964  StateMgr::mCur
    u8 pad965[0x984 - 0x965];
    s32 m984;                // +0x984  saved initial state
    u8 m988;                 // +0x988

    void changeState(s32 state, s32 flag);
};

#endif
