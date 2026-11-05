// Types recovered from 0x674F4C  EnemyBase::EnemyBase(const ActorParam*, s32 numStates, ActorA* owner)
// (soldier base ctor, 1648 bytes).  Every offset below is proven by an instruction of 0x674F4C or of a
// callee; the evidence address is written next to the declaration.
//
// Object layout of the class under construction (offsets in the 0x674F4C disassembly, `this` = r4):
//   +0x000  ActorPrimary   (primary polymorphic base, vptr)      str r2,[r0]         @0x674F68
//   +0x320  ActorSecondary (secondary polymorphic base, vptr)    str r1,[r0]+0x320   @0x674F70
//   +0x90C  StateMgr       (state machine)                       bl 0x10A794        @0x674F74
//   +0x930  Hook mHookA    {type, owner, pmf}                    str r1,[r0,#4]!    @0x674F98
//   +0x940  Hook mHookB                                          str r1,[r0,#0x10]  @0x674FA0
//   +0x950  Hook mHookC                                          stm r2,{r1,r4}     @0x674FBC
//   +0x97C  scalars {0, 20, -1, 0} + five bools                  @0x674FC4..0x674FE4

#ifndef ENEMYBASE_ACTOR_TYPES_H
#define ENEMYBASE_ACTOR_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

struct ActorParam;
struct Heap;
struct EnemyBase;

// Pointer to a state handler that is a member of the actor class.  8 bytes: {fn, this-adjust} -
// events: the arrays below are indexed with stride 8 and filled with `ldrd`/`strd` pairs.
typedef void (EnemyBase::*Func)();


// ---------------------------------------------------------------- allocation
// 0x10BA78 operator new[](u32)                    - POD arrays of the state machine
// 0x10CEE0 operator new[](u32, Heap*, s32)        - arrays of classes with a ctor; heap 0 = current
void* operator new[](unsigned int size) throw();
void* operator new[](unsigned int size, Heap* heap, s32 align) throw();
void  operator delete[](void* p) throw();

// ---------------------------------------------------------------- sead-ish strings
// 0x6F5988  vtable of SafeString            (temporary {vptr, text} built at sp+0x10 @0x67518C)
// 0x10BDF0  FixedSafeString<24>::FixedSafeString():  [4] = this+0xC, [8] = 24, [0] = vtable
// 0x689800  Buffered::copy(const SafeString&, s32 count)  (this = dest; reads dest+4 text, dest+8 cap)
struct SafeString {
    virtual void assureTermination() const;   // vtable slot used by SafeString::length (0x689800)
    const char* mText;                        // +0x4
    SafeString(const char* s) : mText(s) {}
    // The class allocates through the engine's (heap, align) array allocator (0x10CEE0); the defaults
    // are what the two `mov r1,#0 / mov r2,#4` before the call in 0x674F4C pass.
    static void* operator new[](u32 size, Heap* heap = 0, s32 align = 4) throw();
};

struct Buffered : SafeString {                // +0x8 capacity
    s32 mCapacity;
    s32 copy(const SafeString& src, s32 count);   // 0x689800
};

// sizeof == 0x24 for N == 24 (array stride 0x24 in `add r0,r0,#0x24` / vec_ctor size 0x24, @0x675150)
template <int N>
struct FixedSafeString : Buffered {
    char mBuffer[N];                          // +0xC
    FixedSafeString();                        // 0x10BDF0 (out of line)
    ~FixedSafeString();                       // makes armcc write the {elem size, n} array cookie
};

// ---------------------------------------------------------------- state handler table
// 0x69A67C: flat array of 8-byte pointer-to-members of the actor class, indexed with constant indices
// by every enemy ctor of this family (this ctor uses indices 1..27, the sibling 0x6733C4 uses 0x1E..).
// Entries carry adjust == 0, i.e. single inheritance.
extern const Func ro_0069A67C[];

// 0x6F4BA8 / 0x6F77A0: per-class 12-byte / 16-byte rodata descriptors handed to the Hook objects.
extern const u8 ro_006F4BA8[];
extern const u8 ro_006F77A0[];

// ---------------------------------------------------------------- state machine
// 0x10A794 StateMgrBase::StateMgrBase(): [0]=0, [4]=-1, [5]=-1, [6]=0, [8]=0, [0xC]=0, [0x10]=0
struct StateMgrBase {
    u32 mCounter;        // +0x00
    s8  mCur;            // +0x04  (init -1)
    s8  mNext;           // +0x05  (init -1)
    u8  mNum;            // +0x06  (state count, set by 0x674F4C @0x67504C)
    u8  mPad7;
    u32 mNameCount;      // +0x08  numStates (`strne sl,[r5,#8]` @0x675168)
    void* mNames;        // +0x0C  FixedSafeString<24>* (`strne r0,[r5,#0xc]` @0x67516C)
    void* mTimeline;     // +0x10  (cleared by 0x10A794, never touched by this ctor)
    StateMgrBase();
};

// 0x24 bytes total (StateMgrBase + 4 words); the ctor of this class is inlined into 0x674F4C after the
// 0x10A794 call: [0x14]=0 @0x674F7C, [0x18]=0 @0x674F80, [0x1C]=0 @0x674F88, [0x20]=0 @0x674F90.
template <class T>
struct StateMgrT : StateMgrBase {
    T*    mOwner;        // +0x14  = owner (0x674F4C: str r7,[r4,#0x920])
    Func* mEnter;        // +0x18  enter[]  (strd r0,r1,[r5,#0x18]: base, base+8*mNum @0x675080)
    Func* mExec;         // +0x1C  exec[]   (second half of the same 16*n allocation)
    Func* mExit;         // +0x20  exit[]   (str r0,[r5,#0x20] @0x6750C8, 8*n allocation)

    StateMgrT() : mOwner(0), mEnter(0), mExec(0), mExit(0) {}

    // Bounds-checked name accessor: `i < mNameCount ? mNames[i] : mNames[0]`.  Inlined at each of the
    // nine call sites as `cmp <count>,#i ; addhi <names>,#0x24*i` (@0x6751F4, 0x675254, ... 0x675470);
    // for i == 0 both arms are the same address, so the compare disappears (@0x675194).
    FixedSafeString<24>& nameAt(u32 i) {
        FixedSafeString<24>* names = (FixedSafeString<24>*)mNames;
        if (i < mNameCount) return names[i];
        return names[0];
    }
    void setName(u32 i, const SafeString& name) { nameAt(i).copy(name, -1); }

    // Builds the three handler arrays and the name array.  Inlined into 0x674F4C with `this` =
    // &mStateMgr held in r5 (`add r5,r4,#0x800 / add r5,r5,#0x10c` @0x675054):
    //   [r5,#6] mNum, [r5,#0x18] enter, [r5,#0x20] exit, [r5,#8] name count, [r5,#0xC] names.
    // The enter/exec half of the 16*n allocation is filled with ro_0069A67C[0] (a null PMF) and the
    // exit array with ro_0069A67C[1] (the shared no-op exit used by five of the nine states); the
    // per-state table below then overwrites the slots it cares about.
    void init(u8 n) {
        s32 total = (s32)n * 2;
        Func* f = new Func[total];
        mEnter = f;
        mExec = f + mNum;
        for (s32 i = 0; i < total; i++) f[i] = ro_0069A67C[0];
        s32 cnt = mNum;
        Func* e = new Func[cnt];
        mExit = e;
        for (s32 i = 0; i < cnt; i++) e[i] = ro_0069A67C[1];
        mNames = new FixedSafeString<24>[n];
        mNameCount = n;
    }
    // Installs one state's three handlers.  Written as a helper because the original loads all six
    // PMF words before any store (probe: direct assignments interleave, parameter passing does not).
    void set(u32 i, Func enter, Func exec, Func exit) { mEnter[i] = enter; mExec[i] = exec; mExit[i] = exit; }
};

// ---------------------------------------------------------------- polymorphic bases
// The class has two polymorphic base subobjects; after the base ctor (0x2F9858) the compiler stores
//   0x6E61D0          at +0x000   and   0x6E61D0+0x88  at +0x320      (@0x674F64..0x674F70)
// i.e. the secondary vtable sits 0x88 bytes into the vtable group (0x80 = 32 primary slots, then the
// 8-byte {offset-to-top = -0x320, RTTI} header seen at 0x6E6250).  The base ctor itself stores
// 0x6DE230 / 0x6DE230+0x88 for its own class (0x2F9870..0x2F9884), so the base has the same 32 slots.
struct ActorPrimary {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    u8  pad_04[0x54 - 4];
    s16 m54;                              // +0x54  (ldrsh @0x675020, passed as argument 5 of 0x14EB8C)
    u8  pad_56[0x2cc - 0x56];
    u32 m2cc;                             // +0x2CC (copied to the stack @0x675014 for 0x14EB8C)
    u8  pad_2d0[0x320 - 0x2d0];
};

struct ActorSecondary {                   // +0x320
    virtual void s0();
};

// The third ctor argument is the fully derived actor object itself: the only caller seen (0x1B11F8,
// Soldier::Soldier) passes `mov r3,r0` - its own `this` - and 0x674F4C uses it unadjusted, so the
// parameter is a pointer to this same class (offset 0).  The two fields it writes are inherited:
// 0x354: the actor's StateMgr pointer, 0x35A: u16 state count.

// ---------------------------------------------------------------- the state hook objects
// 16-byte objects at +0x930/+0x940/+0x950: { rodata descriptor, owner, state handler PMF }.
// The descriptors are 12-byte records {function, 0, 0} in a per-class table
// (0x6F4B9C for the sibling ctor 0x6733C4, 0x6F4BA8 here; 0x6F7790 / 0x6F77A0 for the third one,
// 16-byte stride), so they are class-specific vtables/type descriptors of the wrapped handler.
struct Hook {
    const void* mType;                    // +0x0  ro_006F4BA8 / ro_006F77A0
    EnemyBase*  mOwner;                   // +0x4  = this
    Func        mFunc;                    // +0x8  PMF from ro_0069A67C (8 bytes)
    Hook(const void* t, EnemyBase* o, Func f) : mType(t), mOwner(o), mFunc(f) {}
};

// ---------------------------------------------------------------- base class
// 0x2F9858 EnemyBase0::EnemyBase0(const ActorParam*, s32, ActorA*)  (calls 0x4FD464)
// 0x4FD464 EnemyBase::EnemyBase(EnemyArg*, ParamTable*) - the two-vtable root actor ctor.
// 0x4FD464 allocates it with operator new(0x64); 0x674F4C zeroes byte +0x61.
struct ActorSub420 { u8 pad0[0x61]; u8 m61; u8 pad1[2]; };

struct EnemyBase0 : ActorPrimary, ActorSecondary {
    EnemyBase0(const ActorParam*, s32, EnemyBase*);
    u8  pad_324[0x354 - 0x324];
    void* m354;                           // +0x354 = &mStateMgr   (str r5,[r7,#0x354] @0x675178)
    u8  pad_358[2];
    u16 m35a;                             // +0x35A = (u16)numStates (strh r8,[0x35A,r7] @0x675184)
    u8  pad_35c[0x3a0 - 0x35c];
    void* m3a0;                           // +0x3A0 (arg3 of 0x14EB8C, loaded @0x675038)
    u8  pad_3a4[0x3ec - 0x3a4];
    void* m3ec;                           // +0x3EC = &mHookB          (str r1,[r4,#0x3ec] @0x674FFC)
    u8  pad_3f0[0x420 - 0x3f0];
    ActorSub420* m420;                    // +0x420 (arg1 of 0x14EB8C, 0x64-byte object from 0x4FD464)
    u32   m424;                           // +0x424 (arg2 of 0x14EB8C)
    u8  pad_428[0x59c - 0x428];
    u32   m59c;                           // +0x59C bit 0x80 cleared  (bic/str @0x67505C)
    u8  pad_5a0[0x77d - 0x5a0];
    u8 m77d;                              // +0x77D = 11
    u8 m77e;                              // +0x77E = -1
    u8 m77f;                              // +0x77F = 0
    u8  pad_780[0x804 - 0x780];
    void* m804;                           // +0x804 = &mHookC
    u8  pad_808[0x90c - 0x808];
};

// 0x14EB8C: copies (m420,m424,m3a0) into an actor param block, resolves the handle at m2cc and stores
// a float at +0x1C.  Its own definition reads argument 6 with `vldr s16,[sp,#0x24]`, i.e. as f32,
// while this call site passes the address of mHookA - the two translation units disagree about the
// type of parameter 6 (the callee only copies the 4 bytes through).  Argument 8 is unused by the callee.
void func_0014EB8C(void* a, u32 b, void* c, const u32* handle, s32 e, void* hook, s32 g, u32 h);

// 0x2AF5FC: { ldr r0,[r0,#0x510] } + nop'ed tail call; the second argument is not read.
void func_002AF5FC(EnemyBase* self, s32 mode);

// ---------------------------------------------------------------- the class under construction
struct EnemyBase : EnemyBase0 {
    EnemyBase(const ActorParam*, s32 numStates, EnemyBase* owner);

    StateMgrT<EnemyBase> mStateMgr;       // +0x90C .. +0x930
    Hook mHookA;                          // +0x930  ro_006F4BA8, pmf = ro_0069A67C[4]
    Hook mHookB;                          // +0x940  ro_006F4BA8, pmf = ro_0069A67C[3]
    Hook mHookC;                          // +0x950  ro_006F77A0, pmf = ro_0069A67C[2]
    u8   pad_960[0x97c - 0x960];
    u32  m97c;                            // +0x97C = 0
    s32  m980[2];                         // +0x980 = {20, -1}  (the original stores the two words with
                                          //   one `stm r2,{r1,fp}`, 20 coming from a register and -1
                                          //   from the fp constant set up at 0x674F94)
    u32  m988;                            // +0x988 = 0
    u8   m98c, m98d, m98e, m98f, m990;    // +0x98C..+0x990 = false
};

#endif
