// Actor class family (ActorBase dtor 0x1510A4): most-derived class destructor.
// Target: vptr stores for ro_6D5A14 (leaf) at +0x0/+0x320, MemP member at 0x98c,
// then the inlined ActD (ro_6EB7B0) body -> mB/mA at 0x868/0x864, then ActC
// (ro_6D2174) -> mX/mY, then ActB (ro_6E0B24) -> mZ at 0x410, then ~ActorBase.
typedef unsigned char u8;
typedef unsigned int u32;



#include "actor.h"

struct MemX { ~MemX(); char pad[0x54]; };    // dtor 0x35D6D0
struct MemY { ~MemY(); char pad[0x2e4]; };   // dtor 0x503368
struct MemZ { ~MemZ(); char pad[0x68]; };    // dtor 0x4EE540
class ActB : public ActorBaseExt {              // vtable ro_6E0B24, 2nd at +0x5c
public:
    virtual ~ActB() {}
    MemZ mZ;                                 // +0x410
};
class ActC : public ActB {                   // vtable ro_6D2174, 2nd at +0x98
public:
    virtual ~ActC() {}
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
    virtual void c31(); virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    MemY mY;                                 // +0x478
    MemX mX;                                 // +0x75c
};
extern "C" void func_0036D0E0(void*);
struct MemP { u32 w; ~MemP() { func_0036D0E0(this); } };
class ActD : public ActC {                   // vtable ro_6EB7B0, 2nd at +0xb8
public:
    virtual ~ActD();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    u8 pad2[0x864 - 0x7b0];
    MemP mA;                                 // +0x864
    MemP mB;                                 // +0x868
};
ActD::~ActD() {}
class ActE : public ActD {
public:
    virtual ~ActE();
};
ActE::~ActE() {}
class ActH : public ActE {                   // vtable ro_6D5A14 is the leaf's own
public:
    virtual ~ActH();
    u8 padh[0x98c - 0x86c];
    MemP m98c;                               // +0x98c
};
ActH::~ActH() {}
