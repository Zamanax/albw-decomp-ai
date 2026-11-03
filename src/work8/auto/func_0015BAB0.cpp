typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;
struct BitFlag32 {
  u32 v;
  void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
  void set(u32 m) { change(m, true); }
  void reset(u32 m) { change(m, false); }
};
struct Sub {
  char pad[0x3a4];
  f32 f;
};
struct Obj {
  char pad0[0x59c];
  BitFlag32 m59c;
  char pad1[0x960 - 0x5a0];
  void* child;
  char pad2[0x9ae - 0x964];
  u8 f9ae;
  char pad3[0xc00 - 0x9af];
  Sub sub;
};
extern void func_004FC07C(Obj*, s32, s32, u32);
extern void func_002228D0(void*, s32, s32);
extern void func_0015D0E0(Obj*);

void phase(Obj* p, s32 n) {
  func_004FC07C(p, n, -1, 0);
  if (p->child) func_002228D0(p->child, n, -1);
  func_0015D0E0(p);
  p->m59c.reset(7);
  p->f9ae = 0;
  p->sub.f = 1.0f;
}

extern "C" void target(Obj* p) { phase(p, 1); }
