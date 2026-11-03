typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned long long u64;
// 0x373A60: D1 destructor of the class owning vtable ro_006E5394 (second vtable at +0xc8).
// Chain: own vptr pair -> member at +0x9BC (dtor 0x5027C4) -> base 0x6EB7B0 level (members
// +0x868/+0x864 -> 0x36D0E0) -> base 0x6D2174 level (+0x75C -> 0x35D6D0, +0x478 -> 0x503368)
// -> base 0x6E0B24 level (+0x410 -> 0x4EE540) -> ActorBase dtor 0x1510A4 (tail call).
struct ActorBaseA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ~ActorBaseA();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    virtual void v9();  virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    char padA[0x320 - 4];
};
struct ActorBaseB {
    virtual void b0();
    char padB[0x410 - 0x324];
};
class ActorBase : public ActorBaseA, public ActorBaseB {
public:
    virtual ~ActorBase();
};
struct MemX { ~MemX(); char pad[0x54]; };     // dtor 0x35D6D0
struct MemY { ~MemY(); char pad[0x2e4]; };    // dtor 0x503368
struct MemZ { ~MemZ(); char pad[0x68]; };     // dtor 0x4EE540
struct MemW { ~MemW(); char pad[0x8c]; };     // dtor 0x5027C4
class ActB : public ActorBase {
public:
    virtual ~ActB() {}
    MemZ mZ;
};
class ActC : public ActB {
public:
    virtual ~ActC() {}
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
    virtual void c31(); virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    MemY mY;
    MemX mX;
};
extern "C" void func_0036D0E0(void*);
struct MemP { u32 w; ~MemP(){ func_0036D0E0(this); } };
class ActD : public ActC {
public:
    virtual ~ActD();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    u8 pad2[0x864 - 0x7b0];
    MemP mA;
    MemP mB;
};
ActD::~ActD() {}
class ED : public ActD { public: virtual ~ED(); };
ED::~ED() {}
class ActG : public ED {
public:
    virtual ~ActG();
    virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
    u8 padg[0x9bc - 0x86c];
    MemW mX;
};
ActG::~ActG() {}
