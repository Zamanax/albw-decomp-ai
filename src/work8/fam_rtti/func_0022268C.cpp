#include "../../work7/ds2/ds2.h"



#include "actor.h"

class Base6EDB00 : public ActorBaseExt {
public:
    void finalize() {}
    virtual ~Base6EDB00() { finalize(); }
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
};
void func_0036D0E0(void*);
struct Mem96 { ~Mem96(); char pad[0x2c]; };
struct Mem9AC : Mem96 {};
struct Mem4 { ~Mem4() { func_0036D0E0(this); } u32 v; };

class X0022268C : public Base6EDB00 {
public:
    virtual ~X0022268C();
    char pad[0x8bc - 0x410];
    Mem4 m8bc;
    char pad2[0x8e8 - 0x8c0];
    Mem9AC m968;
};

X0022268C::~X0022268C() {}
