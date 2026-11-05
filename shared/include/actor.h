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
// Secondary base: +0x320..0x40C (0xEC bytes).  The constructors prove the end: 0x1DEA54 puts
// Player's first member at +0x40C and 0x4FD490 zeroes EnemyBase's first word there.  54 matched
// sources instead spell its extent as `char padB[0x410 - 0x324]` (0xF0), i.e. they fold the
// enemy base's +0x40C handle word into the base; those sources use ActorBaseExt below.
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
// that spell the npc without virtual slots (plain pad arrays) generate the same access offsets.
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



// ---------------------------------------------------------------------------------------------
// EnemyBase: ctor 0x4FD464, 0x8BC bytes, 31 primary vtable slots (vtable ro_006EDB00, secondary
// vtable at +0x84 = 0x6EDB00+0xb8 stored at +0x320).  Derived enemy constructors put their first
// member at +0x8BC (0x206FBC, 0x22141C).  Every offset below is a store target in 0x4FD464:
//   +0x40C..+0x41C zeroed (0x4FD490), +0x420 = new 0x64-byte object (0x4FD4B4), +0x438 new 0x0C
//   (0x4FD4E4), +0x43C new 0x48 (0x4FD51C), delegates at +0x440/+0x444/+0x448 = &m524/&m534/&m544,
//   Vec3 pairs from +0x44C, +0x4C4..+0x4CC = 1.0f, +0x4DC = 8, +0x508..+0x50E = 4, +0x510 new
//   0x2C4 (0x4FD640), five 16-byte delegates at +0x514..+0x563, +0x584..+0x58C = 0x1F08/0x36/0xDDF,
//   +0x59C = 0x1F390003, +0x5A4 = m5a0, +0x658 20x{0,0,1.0f}, +0x77C = 1, +0x782 = 0x5A,
//   +0x798 = 1.2f, +0x850 = 2, +0x87C..+0x881 = 0xA/0x14/0x28/0xA/0xF/5.
struct EnemyParam;

class EnemyBase : public ActorBase {
public:
    EnemyBase(void* arg, EnemyParam* param);   // 0x4FD464

    // 10 more primary slots than ActorBase's 21: 31 slots, so the secondary vtable sits at +0x84
    // inside ro_006EDB00 (0x4FD484 stores r1+0x84 at this+0x320).
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30();

    u32 m40c;                  // +0x40C  (0x4FD490) actor handle, later func_0014E428 (0x4FDBFC)
    u32 m410;                  // +0x410
    u32 m414;                  // +0x414
    u32 m418;                  // +0x418
    u32 m41c;                  // +0x41C
    void* m420;                // +0x420  new 0x64 (0x4FD4B4)
    u32 m424;                  // +0x424
    u32 m428;                  // +0x428..0x434
    u32 m42c;
    u32 m430;
    u32 m434;
    void* m438;                // +0x438  new 0x0C (0x4FD4E4)
    void* m43c;                // +0x43C  new 0x48 (0x4FD51C)
    void* m440;                // +0x440  = &m524
    void* m444;                // +0x444  = &m534
    void* m448;                // +0x448  = &m544
    Vec3 m44c;                 // +0x44C  sead Vector3f::zero
    Vec3 m458;                 // +0x458
    Vec3 m464;                 // +0x464  zero
    Vec3 m470;                 // +0x470
    Vec3 m47c;                 // +0x47C  zero
    Vec3 m488;                 // +0x488
    Vec3 m494;                 // +0x494  zero
    Vec3 m4a0;                 // +0x4A0
    u32 m4ac;                  // +0x4AC
    u32 m4b0;                  // +0x4B0
    u8 m4b4;                   // +0x4B4
    u8 m4b5;                   // +0x4B5
    u8 pad4b6[2];
    Vec3 m4b8;                 // +0x4B8  zero
    f32 m4c4;                  // +0x4C4  1.0f
    f32 m4c8;                  // +0x4C8  1.0f
    f32 m4cc;                  // +0x4CC  1.0f
    Vec3 m4d0;                 // +0x4D0  zero
    u8 m4dc;                   // +0x4DC  8
    u8 pad4dd[3];
    u32 m4e0;                  // +0x4E0  m2d0->m1c8[param->m8] (0x4FDBE0)
    Vec3 m4e4;                 // +0x4E4
    f32 m4f0;                  // +0x4F0  1.0f
    f32 m4f4;                  // +0x4F4  1.0f
    f32 m4f8;                  // +0x4F8  1.0f
    u32 m4fc;                  // +0x4FC
    u32 m500;                  // +0x500
    u32 m504;                  // +0x504
    u16 m508;                  // +0x508  4
    u16 m50a;                  // +0x50A  4
    u16 m50c;                  // +0x50C  4
    u16 m50e;                  // +0x50E  4
    void* m510;                // +0x510  new 0x2C4 (0x4FD640)
    u8 m514[0x68];             // +0x514..0x57B five 16-byte delegates (see Delegate below)
    f32 m57c;                  // +0x57C
    f32 m580;                  // +0x580
    u32 m584;                  // +0x584  0x1F08
    u32 m588;                  // +0x588  0x36
    u32 m58c;                  // +0x58C  0xDDF
    Vec3 m590;                 // +0x590  zero
    u32 m59c;                  // +0x59C  0x1F390003
    u32 m5a0;                  // +0x5A0  0x3000
    u32 m5a4;                  // +0x5A4  = m5a0
    u8 m5a8[0xb0];             // +0x5A8..0x657 sub object (7x12-byte entries, 7 pointers, ...)
    u8 m658[0xf0];             // +0x658..0x747 20 x {0,0,1.0f}
    u8 m748[0x20];             // +0x748..0x767 2 x 16-byte sub objects
    u8 m768;                   // +0x768
    u8 pad769[3];
    u8 m76c;                   // +0x76C
    u8 pad76d[3];
    Vec3 m770;                 // +0x770
    u8 m77c;                   // +0x77C  1
    s8 m77d;                   // +0x77D  -1
    s8 m77e;                   // +0x77E  -1
    u8 m77f;                   // +0x77F
    s8 m780;                   // +0x780  -1
    u8 pad781;
    u16 m782;                  // +0x782  0x5A
    u16 m784;                  // +0x784
    u16 m786;                  // +0x786  -1
    u16 m788;                  // +0x788  -1
    u8 pad78a[0xe];
    f32 m798;                  // +0x798  1.2f
    u32 m79c;                  // +0x79C
    u32 m7a0;                  // +0x7A0
    u32 m7a4;                  // +0x7A4
    Vec3 m7a8;                 // +0x7A8  zero
    u8 m7b4[0x48];             // +0x7B4..0x7FB in-place 0x48-byte sub object ctor 0x34CAA0
    u8 m7fc;                   // +0x7FC
    u8 pad7fd[3];
    u8 m800[0x24];             // +0x800..0x823 zeroed words
    u8 m824[4];                // +0x824..0x827 0xFF
    u8 m828[3];                // +0x828..0x82A zero
    u8 pad82b;
    Vec3 m82c;                 // +0x82C  zero
    u16 m838;                  // +0x838
    u8 pad83a[2];
    Vec3 m83c;                 // +0x83C  zero
    u8 m848[3];                // +0x848..0x84A zero
    u8 pad84b;
    f32 m84c;                  // +0x84C
    u8 m850;                   // +0x850  2
    u8 m851;                   // +0x851
    u8 m852;                   // +0x852
    u8 m853;                   // +0x853
    f32 m854;                  // +0x854
    u8 m858;                   // +0x858  1
    u8 m859;                   // +0x859
    u8 m85a;                   // +0x85A
    u8 m85b;                   // +0x85B
    u32 m85c;                  // +0x85C
    u32 m860;                  // +0x860
    f32 m864;                  // +0x864  1.0f
    u32 m868;                  // +0x868
    u32 m86c;                  // +0x86C
    f32 m870;                  // +0x870  1.0f
    u8 m874[4];                // +0x874..0x877 0x80
    u32 m878;                  // +0x878
    u8 m87c;                   // +0x87C  0xA
    u8 m87d;                   // +0x87D  0x14
    u8 m87e;                   // +0x87E  0x28
    u8 m87f;                   // +0x87F  0xA
    u8 m880;                   // +0x880  0xF
    u8 m881;                   // +0x881  5
    u8 m882;                   // +0x882
    u8 pad883;
    void* m884;                // +0x884  = &m884
    void* m888;                // +0x888  = &m884
    u32 m88c;                  // +0x88C
    u32 m890;                  // +0x890  0x28
    u8 m894;                   // +0x894
    u8 m895;                   // +0x895
    u8 m896;                   // +0x896  1
    u8 m897;                   // +0x897
    f32 m898;                  // +0x898
    u8 m89c[4];                // +0x89C..0x89F zero
    u32 m8a0;                  // +0x8A0
    u32 m8a4;                  // +0x8A4
    Vec3 m8a8;                 // +0x8A8  zero
    u8 m8b4;                   // +0x8B4
    u8 m8b5;                   // +0x8B5
    u8 m8b6;                   // +0x8B6
    u8 m8b7;                   // +0x8B7  1
    u8 m8b8;                   // +0x8B8
    u8 pad8b9[3];              // sizeof == 0x8BC
};

// ---------------------------------------------------------------------------------------------
// Delegate: 16 bytes {vptr, object, pointer-to-member function}.  vtable ro_006F4554; its slot 0
// (0x6830E8) decodes the member pointer: mObj == 0 -> return 0, otherwise r0 = mObj + (adj >> 1)
// and (adj & 1) loads the vtable for a virtual member.  A concrete owner type makes this a
// template; the game has one instantiation per owner class.
template <class T>
class Delegate {
public:
    Delegate() : mObj(0), mFunc(0) {}
    Delegate(T* o, void (T::*f)()) : mObj(o), mFunc(f) {}
    virtual void invoke();
    T* mObj;                   // +0x04
    void (T::*mFunc)();        // +0x08
};

// ---------------------------------------------------------------------------------------------
// The actor parameter record handed to every actor constructor (ActorParam* in 0x150E40,
// EnemyArg*/EnemyParam* in 0x4FD464, NpcBase's 5th argument in 0x623368).  Only the fields the
// matched constructors read are modelled: the record is at least 0x2a4 bytes, the rail indices at
// +0x29c/+0x2a0 are read by 0x2CC998/0x2CC9A4, and +0x1c by 0x1E4414.
struct ActorParam {
    u8 pad000[0x1c];
    u32 m1c;                   // +0x01C  (0x1E4414 reads it)
    u8 pad020[0x29c - 0x20];
    s32 m29c;                  // +0x29C  rail index (negative = "no rail")  0x2CC998
    s32 m2a0;                  // +0x2A0  second rail check                 0x2CC9A4
};

#endif
