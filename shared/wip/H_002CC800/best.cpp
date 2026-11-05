// 0x002CC800  TurtleMother::TurtleMother(ActorParam*)   2836 bytes, 11 states, 2 model holders.
// Reconstruction from the disassembly; see actor_types.h for every layout claim and its evidence.

#include "actor_types.h"

// ------------------------------------------------------------------ allocation / formatting aid
struct NoThrow {};
void* operator new(u32 size, NoThrow);
void* operator new[](u32 size);
void* operator new[](u32 size, void* heap, s32 align);
inline void* operator new(u32, void* p) { return p; }



// ------------------------------------------------------------------ externs seen in the listing
// 0x2CC934: FlagMgr::check, manager pointer loaded from data_0070B728
extern FlagMgr* data_0070B728;
// 0x2CC9B0: rail manager object, getRails() -> PtrArray<Rail>*
struct RailMgr {
    PtrArray<Rail>* getRails();          // 0x582250
};
extern RailMgr* data_0070C8E0;
// 0x2CCFA0: ModelMgr::regist(Model*, s32)
struct ModelMgr {
    void regist(Model* m, s32 kind);     // 0x4A7F00
};
extern ModelMgr* data_00709D28;
// 0x2CC980: address passed as the 5th argument of func_004BE114
extern u8 data_0070EFF0[];
// 0x2CD260: address passed to func_004C03B8
extern u8 bss_00780CD8[];

// 0x4BE114: 5 arguments, forwards (self, a, 0, g) to 0x4BDCEC and tail-calls the next function
void func_004BE114(void* self, s32 a, s32 b, const sead::SafeString& tag, void* g);
void func_004BD280(void* self, s32 a, s32 b);             // 0x4BD280
void func_00622780(void* self, s32 a, s32 b);             // 0x622780
void func_004BDB04(void* self);                           // 0x4BDB04
void func_004C03B8(void* self, void* g);                  // 0x4C03B8
void func_004BC8D8(void* self);                           // 0x4BC8D8
void func_004EDAD0(Model* m, const u32& id);               // 0x4EDAD0
void func_004ED9C8(Model* m);                              // 0x4ED9C8
void func_00435ED0(void* node, const Mtx33* rot);          // 0x435ED0
void func_0043625C(void* node, void* mtx);                 // 0x43625C
struct Res7A0 {
    u32 find(const sead::SafeString& name);                // 0x564A78
};

// ------------------------------------------------------------------ the deltas written at 0x2CCB90..
// 25 member-function-pointer constants; the game's table lives at 0x6A0698 and the constructor
// takes its base in fp (0x2CCA68 ldr fp,[pc,#0x190]).  Order = the order the compiler placed the
// unique constants in, and the constructor reads them at fp+8*index.
class TurtleMother;

class TurtleMother : public NpcBase<TurtleMother> {
public:
    TurtleMother(ActorParam* p);

    // state functions, named after their addresses in the game's table
    void f002CC144(); void f00622C50(); void f006231A0(); void f00622CF0();
    void f006231B0(); void f00622E78(); void f006225C0(); void f002CC464();
    void f002CC188(); void f00623088(); void f00622C04(); void f0062319C();
    void f00622BDC(); void f002CC550(); void f002CC18C(); void f002CC5CC();
    void f002CC4BC(); void f002CC564(); void f002CC1DC(); void f002CC568();
    void f002CC1E0(); void f002CC7B0(); void f002CC644();

    static const Func sFuncs[25];

    u8 pad988[0x98c - 0x988];
    u32 m98c;                            // +0x98c
    u32 m990;                            // +0x990
    Vec3 m998;                           // +0x998
    f32 m9a4;                            // +0x9a4
    u16 m9a8, m9aa, m9ac, m9ae;          // +0x9a8
    u8 m9b0;                             // +0x9b0
    u8 m9b1;                             // +0x9b1  "flags 0x283/0x284/0x285 all set"
    Model* m9b4;                         // +0x9b4
    Model* m9b8;                         // +0x9b8
    NpcControl* m9bc;                    // +0x9bc
    Func m9c8;                           // +0x9c8  = sFuncs[0]
    NpcListener m9c0;                    // +0x9c0  {vptr ro_006F7C98, this}
    u8 m9d0, m9d1, m9d2;                 // +0x9d0
    u32 m9d4, m9d8, m9dc;                // +0x9d4  Res7A0 handles
    u32 m9e0;                            // +0x9e0  = m3e8
    Vec3Table<0x50> mPts;                // +0x9e4 .. +0xda3
    u32 mda4;                            // +0xda4  point count
    Vec3 mda8;                           // +0xda8
    u32 mdb4;                            // +0xdb4
    f32 mdb8;                            // +0xdb8
};

const TurtleMother::Func TurtleMother::sFuncs[25] = {
    &TurtleMother::f002CC144,            // 0  also copied into m9c8
    &TurtleMother::f00622C50,            // 1  state 0 enter
    &TurtleMother::f006231A0,            // 2  state 0 exec
    0,                                   // 3  "no state function"
    &TurtleMother::f00622CF0,            // 4  state 1 enter
    &TurtleMother::f006231B0,            // 5  state 1 exec
    &TurtleMother::f00622E78,            // 6  state 2 enter
    &TurtleMother::f006225C0,            // 7  state 2 exec
    &TurtleMother::f002CC464,            // 8  state 8 enter
    &TurtleMother::f002CC188,            // 9  state 8 exec
    &TurtleMother::f00623088,            // 10 state 8 exit (overwritten later)
    &TurtleMother::f00622C04,            // 11 state 4 enter
    &TurtleMother::f0062319C,            // 12 state 4 exec
    &TurtleMother::f00622BDC,            // 13 state 4 exit
    &TurtleMother::f002CC550,            // 14 state 5 enter
    &TurtleMother::f002CC18C,            // 15 state 5 exec
    &TurtleMother::f002CC5CC,            // 16 state 6 enter
    &TurtleMother::f002CC4BC,            // 17 state 6 exec
    &TurtleMother::f002CC564,            // 18 state 7 enter
    &TurtleMother::f002CC1DC,            // 19 state 7 exec
    &TurtleMother::f002CC568,            // 20 state 9 enter
    &TurtleMother::f002CC1E0,            // 21 state 9 exec
    &TurtleMother::f002CC7B0,            // 22 state 10 enter
    &TurtleMother::f002CC644,            // 23 state 10 exec
    0,                                   // 24 the fill value for the unused slots
};

void StateNames::allocBuffer(s32 n) {
    u32* base = (u32*)::operator new[]((u32)(n * sizeof(sead::FixedSafeString<24>) + 8), (void*)0, 4);
    if (!base) return;
    base[0] = sizeof(sead::FixedSafeString<24>);
    base[1] = (u32)n;
    sead::FixedSafeString<24>* arr = (sead::FixedSafeString<24>*)(base + 2);
    for (s32 i = 0; i < n; i++) new (&arr[i]) sead::FixedSafeString<24>();
    mCount = (u32)n;
    mPtr = arr;
}

static inline NpcInitParam makeInitParam() {
    NpcInitParam np = {0, 0, 0, 0, 1};
    return np;
}

TurtleMother::TurtleMother(ActorParam* p)
    : NpcBase(p, 0, -1, makeInitParam()),
      m98c(0), m990(0), m998(0.0f, 0.0f, 0.0f), m9a4(1.0f),
      m9a8(0), m9aa(0), m9ac(0), m9ae(0), m9b0(0), m9b1(0), m9b4(0), m9b8(0),
      m9bc(new ((NoThrow())) NpcControl()),
      m9c8(sFuncs[0]),
      m9c0(this),
      m9d0(0), m9d1(0), m9d2(0), m9d4(0), m9d8(0), m9dc(0), m9e0(m3e8), mda4(0) {
    // 0x2CC920..0x2CC96C: save flag: states 0x283/0x284/0x285 all set -> "second form"
    if (data_0070B728->check(0x283) && data_0070B728->check(0x284) && data_0070B728->check(0x285))
        m9b1 = 1;

    // 0x2CC96C..0x2CC994: (this, 6, 0, tag, data_0070EFF0)
    func_004BE114(this, 6, 0, sead::SafeString("\x83\x5e\x81\x5b\x83\x67\x83\x8b\x83\x7d\x83\x55\x81\x5b"),
                  data_0070EFF0);

    // 0x2CC998..0x2CCA30: copy up to 0x50 rail points into mPts
    if (p->m29c >= 0 && p->m2a0 >= 0) {
        Rail* rail = data_0070C8E0->getRails()->at(p->m29c);
        u32 n = 0;
        if (rail) {
            RailPoint** pt = rail->points;
            RailPoint** end = pt + rail->pointCount;
            while (pt != end) {
                Vec3& dst = mPts.at(n);
                dst = (*pt)->pos;
                n++;
                pt++;
            }
        }
        mda4 = n;
    }

    // 0x2CCA34..0x2CCA40: mda8 Vec3, mdb4, mdb8
    mda8 = Vec3(0.0f, 0.0f, 0.0f);
    mdb4 = 0;
    mdb8 = 0.0f;

    // 0x2CCB60..0x2CCB74: the state machine points at itself
    m354 = &mStateMgr;
    m35a = 11;

    // 0x2CCA44..0x2CCB08: two function tables of 11 entries each (mEnter at +0x18, mExec = mEnter+11)
    ActorStateMgr<TurtleMother>& sm = mStateMgr;
    sm.mNum = 11;
    sm.mOwner = this;
    // One flat 22-entry array, mExec = mEnter + 11: the target fills it contiguously with a
    // 16-byte stride (0x2CCA7C: stm r2,{r3,ip} / strd r2,r3,[r0]; r0 += 0x10, 11 times).
    Func* tbl = new Func[22];
    sm.mEnter = tbl;
    sm.mExec = tbl + sm.mNum;
    for (s32 i = 0; i < 22; i++) tbl[i] = sFuncs[24];
    // 0x2CCAA4..0x2CCB04: the exit table
    sm.mExit = new Func[sm.mNum];
    for (s32 i = 0; i < 11; i++) sm.mExit[i] = sFuncs[3];
    // 0x2CCB08..0x2CCB5C: names: Buffer<FixedSafeString<24>> of 11 entries
    sm.mNames.allocBuffer(11);

    // 0x2CCB60..0x2CCF0C: per-state functions and names, in the order the game sets them up
    sm.mEnter[0] = sFuncs[1];   sm.mExec[0] = sFuncs[2];   sm.mExit[0] = sFuncs[3];
    sm.setStateName(0, sead::SafeString("cState_Wait"));
    sm.mEnter[1] = sFuncs[4];   sm.mExec[1] = sFuncs[5];   sm.mExit[1] = sFuncs[3];
    sm.setStateName(1, sead::SafeString("cState_Walk"));
    sm.mEnter[2] = sFuncs[6];   sm.mExec[2] = sFuncs[7];   sm.mExit[2] = sFuncs[3];
    sm.setStateName(2, sead::SafeString("cState_Event"));
    sm.mEnter[8] = sFuncs[8];   sm.mExec[8] = sFuncs[9];   sm.mExit[8] = sFuncs[10];
    sm.setStateName(8, sead::SafeString("cState_EventEnd"));
    sm.mEnter[4] = sFuncs[11];  sm.mExec[4] = sFuncs[12];  sm.mExit[4] = sFuncs[13];
    sm.setStateName(4, sead::SafeString("cState_Hide"));
    sm.mEnter[5] = sFuncs[14];  sm.mExec[5] = sFuncs[15];  sm.mExit[5] = sFuncs[3];
    sm.setStateName(5, sead::SafeString("cState_CheckPlayer"));
    sm.mEnter[6] = sFuncs[16];  sm.mExec[6] = sFuncs[17];  sm.mExit[6] = sFuncs[3];
    sm.setStateName(6, sead::SafeString("cState_TurtleDocking"));
    sm.mEnter[7] = sFuncs[18];  sm.mExec[7] = sFuncs[19];  sm.mExit[7] = sFuncs[3];
    sm.setStateName(7, sead::SafeString("cState_DockingWait"));
    sm.mEnter[8] = sFuncs[8];   sm.mExec[8] = sFuncs[9];   sm.mExit[8] = sFuncs[3];
    sm.setStateName(8, sead::SafeString("cState_EventEnd"));
    sm.mEnter[9] = sFuncs[20];  sm.mExec[9] = sFuncs[21];  sm.mExit[9] = sFuncs[3];
    sm.setStateName(9, sead::SafeString("cState_WalkingLake"));
    sm.mEnter[10] = sFuncs[22]; sm.mExec[10] = sFuncs[23]; sm.mExit[10] = sFuncs[3];
    sm.setStateName(10, sead::SafeString("cState_ReCheckPlayerCancel"));
    sm.mEnter[10] = sFuncs[22]; sm.mExec[10] = sFuncs[23]; sm.mExit[10] = sFuncs[3];

    // 0x2CCF10: flag 0x10
    m8ac |= 0x10;

    // 0x2CCF1C..0x2CD12C: the two model holders.  Both buffers are locals of the whole
    // constructor (they live until its end), which is why the frame holds two separate
    // 0x4c-byte FixedSafeString<64> objects: sp+0x68 and sp+0x14 in the original.
    sead::FixedSafeString<0x40> path0;
    sead::FixedSafeString<0x40> path1;

    m9b4 = new ((NoThrow())) Model();
    path0.format("Actor/TurtleMother_0.kcl");
    m9b4->load(path0);
    {
        u32 id = m2cc;
        func_004EDAD0(m9b4, id);
    }
    m9b4->m2c = mActorId;
    data_00709D28->regist(m9b4, 3);

    m9b8 = new ((NoThrow())) Model();
    path1.format("Actor/TurtleMother_1.kcl");
    m9b8->load(path1);
    {
        u32 id = m2cc;
        func_004EDAD0(m9b8, id);
    }
    m9b8->m2c = mActorId;
    data_00709D28->regist(m9b8, 3);
    m9b8->m28 = &m9c0;                   // 0x2CD138 str r1,[r0,#0x28]

    // 0x2CD13C..0x2CD1B0: orientation of both models from the resource matrix
    {
        Mtx33 rot;
        getRot(&rot, (const Mtx34*)(m7a0 + 0x104));
        if (m9b4) {
            func_00435ED0(m9b4->m14, &rot);
            func_0043625C(m9b4->m14, m3d0);
            func_004ED9C8(m9b4);
        }
        if (m9b8) {
            func_00435ED0(m9b8->m14, &rot);
            func_0043625C(m9b8->m14, m3d0);
            func_004ED9C8(m9b8);
        }
    }
    func_004BDB04(this);
    m8ac &= ~8u;

    // 0x2CD1C8..0x2CD248: which form of the fight this actor is in
    if (m9b1) {
        m853 = 3;
        func_004BD280(this, 3, 0);
        func_00622780(this, 9, 0);
        mInitState = 9;
        m9b4->m44 = 0;
        m9b8->m44 = 1;
        m9d2 = 1;
    } else {
        mInitState = 10;
        m857 = 0;
        func_00622780(this, 5, 0);
        m9b4->m44 = 1;
        m9b8->m44 = 0;
    }

    // 0x2CD24C: virtual call, slot at vtable +0x10, argument 0x24
    {
        void* res = (void*)m7a0;
        void (*fp)(void*, s32) = *(void (**)(void*, s32))((char*)(*(void**)res) + 0x10);
        fp(res, 0x24);
    }

    func_004C03B8(this, bss_00780CD8);   // 0x2CD268
    func_004BC8D8(this);                 // 0x2CD274
    m8ac |= 0x2c40;
    m3ac = -1.0f;

    // 0x2CD290..0x2CD2DC: three joints
    {
        Res7A0* res = (Res7A0*)m7a0;
        m9d4 = res->find(sead::SafeString("TurtleL"));
        m9d8 = res->find(sead::SafeString("TurtleM"));
        m9dc = res->find(sead::SafeString("TurtleS"));
    }
    m857 = 0;
}
