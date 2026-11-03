typedef unsigned char u8;
typedef unsigned int u32;

struct CS { void func_0010C0B8(); void func_0010EEE0(); };

struct Mgr {
  u8 p0[4];
  CS mCS;
};

struct Obj;
extern Mgr* func_00580850(Obj*);

struct P2 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void* v20(int);
};

struct P1 {
  u8 p0[0x10];
  P2* m10;
};

struct Obj {
  u8 p0[0x10];
  P1* m10;
  u8 p1[0x61 - 0x14];
  u8 m61;
  u8 p2[0x15c - 0x62];
  u8 m15c;
};

extern void func_0048FCD4(Obj*);
extern void func_00490AB8(void*, void*);
extern void func_0049F9B0(Obj*, int, void*);

struct Scoped{CS*p;Scoped(CS*t):p(t){t->func_0010C0B8();}~Scoped(){p->func_0010EEE0();}};
void func_0049FD40(Obj* self) {
  func_0048FCD4(self);
  Scoped guard(&func_00580850(self)->mCS);
  P2* p = self->m10 ? self->m10->m10 : 0;
  if (self->m61 != 0) {
    if (p) {
      void* r = p->v20(0xf);
      func_00490AB8(r, (char*)self + 0x15c);
    } else {
      func_0049F9B0(self, 0xf, (char*)self + 0x15c);
    }
  } else {
    func_0049F9B0(self, 0xe, (char*)self + 0x15c);
  }
}
