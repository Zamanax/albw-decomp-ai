typedef unsigned char u8;
typedef unsigned int u32;
// Complete-object destructor chain of the actor class family (ActG -> ActD -> ActC -> ActB -> ActorBase).
// Members are destroyed in reverse declaration order; each level stores its vptr pair before its member dtors.
extern "C" void func_0036D0E0(void*);   // MemP::~MemP
extern "C" void func_002E1B70(void*);   // MemQ::~MemQ
struct MemP { u32 w; ~MemP(){ func_0036D0E0(this); } };   // dtor 0x36D0E0 (no return use)
struct MemQ { u8 pad[0x44]; ~MemQ(){ func_002E1B70(this); } };   // dtor 0x2E1B70 (no return use)
struct MemR { ~MemR(); u8 pad[0x44]; };      // dtor 0x36746C (returns this)
struct MemX { ~MemX(); u8 pad[0x54]; };      // dtor 0x35D6D0 (returns this)
struct MemY { ~MemY(); u8 pad[0x2e4]; };     // dtor 0x503368 (returns this)
struct MemZ { ~MemZ(); u8 pad[0x68]; };      // dtor 0x4EE540 (returns this)
struct ActorBaseA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ~ActorBaseA();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    virtual void v9();  virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    u8 padA[0x320 - 4];
};
struct ActorBaseB {
    virtual void b0();
    u8 padB[0x410 - 0x324];
};
class ActorBase : public ActorBaseA, public ActorBaseB {
public:
    virtual ~ActorBase();   // dtor 0x1510A4
};
class ActB : public ActorBase {
public:
    virtual ~ActB() {}
    MemZ mZ;                                 // +0x410
};
class ActC : public ActB {
public:
    virtual ~ActC() {}
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
    virtual void c31(); virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    MemY mY;                                 // +0x478
    MemX mX;                                 // +0x75c
};
class EC0 : public ActC { public: virtual ~EC0(); };
EC0::~EC0() {}
class EC1 : public EC0 { public: virtual ~EC1(); };
EC1::~EC1() {}
class ActD : public EC1 {
public:
    virtual ~ActD();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    u8 pad2[0x864 - 0x7b0];
    MemP mA;                                 // +0x864
    MemP mB;                                 // +0x868
};
ActD::~ActD() {}
class ED0 : public ActD { public: virtual ~ED0(); };
ED0::~ED0() {}
class ActG : public ED0 {
public:
    virtual ~ActG();
    u8 padg[0x98c - 0x86c];
    MemR mR;                                 // +0x98c
    MemQ mQ;                                 // +0x9d0
};
ActG::~ActG() {}
