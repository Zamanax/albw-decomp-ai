// 0x2E7220 (and its duplicate 0x3A240C): D1 destructor of the leaf class owning vtable pair
// ro_006E5F84 (secondary sub-vtable at +0x84, i.e. 31 primary slots), whose base level owns
// ro_006EDB00 and whose root destructor is func_001510A4.
// Shape: leaf vptr pair (fused with the address of the first member destroyed) -> three 4-byte
// members with destructor func_0036D0E0 at +0x8BC/+0x8C0/+0x8C4, reverse order -> base level
// vptr pair ro_006EDB00 (+0x84 stored at +0x320) -> tail call to the root destructor.
typedef unsigned char u8;
typedef unsigned int u32;

struct Primary { virtual ~Primary();
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18();
  u8 pad[0x31c]; };
struct Secondary { virtual void s0(); u8 pad[0x22c]; };
struct func_001510A4 : Primary, Secondary { virtual ~func_001510A4(); };
extern "C" void func_0036D0E0(void*);
struct MemP { u32 w; ~MemP() { func_0036D0E0(this); } };

class Base6EDB00 : public func_001510A4 {
public:
    void finalize() {}
    virtual ~Base6EDB00() { finalize(); }
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
};

class En210D : public Base6EDB00 {
public:
    virtual ~En210D() {}
    char pad[0x36c];
    MemP m8bc;
    MemP m8c0;
    MemP m8c4;
};

void func_002E7220(En210D* p) { p->En210D::~En210D(); }
