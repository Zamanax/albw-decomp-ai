// 0x3829A4: D1 destructor of the leaf class owning vtable ro_006E5F84 (second vtable at +0x320 -> vt+0x84).
// Chain: leaf vptr pair -> three 4-byte MemP members at +0x8BC/+0x8C0/+0x8C4 (dtor 0x36D0E0, reverse order)
// -> Base6EDB00 level (vt ro_006EDB00, second at +0x320 -> vt+0x84, inline body) -> ActorBase dtor 0x1510A4 (tail call).
typedef unsigned int u32;
extern "C" void func_0036D0E0(void*);



#include "actor.h"

class Base6EDB00 : public ActorBaseExt {
public:
    void finalize() {}
    virtual ~Base6EDB00() { finalize(); }
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
};
struct MemP { u32 w; ~MemP() { func_0036D0E0(this); } };
class En210D : public Base6EDB00 {
public:
    virtual ~En210D();
    char pad410[0x8bc - 0x410];
    MemP m8bc;
    MemP m8c0;
    MemP m8c4;
};
En210D::~En210D() {}
