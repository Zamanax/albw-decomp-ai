// 0x3829A4: D1 destructor of the leaf class owning vtable ro_006E5F84 (second vtable at +0x320 -> vt+0x84).
// Chain: leaf vptr pair -> three 4-byte MemP members at +0x8BC/+0x8C0/+0x8C4 (dtor 0x36D0E0, reverse order)
// -> Base6EDB00 level (vt ro_006EDB00, second at +0x320 -> vt+0x84, inline body) -> ActorBase dtor 0x1510A4 (tail call).
typedef unsigned int u32;
extern "C" void func_0036D0E0(void*);
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
    virtual ~ActorBase();                    // 0x1510A4
};
class Base6EDB00 : public ActorBase {
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
