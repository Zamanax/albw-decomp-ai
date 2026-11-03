typedef int s32;
typedef unsigned int u32;
struct Obj {
  char pad0[0x91c];
  u32 f91c;
  char pad1[0x960 - 0x920];
  void* child;
};
extern void func_004FC07C(Obj*, s32, s32, u32);
extern void func_002228D0(void*, s32, s32);
extern void func_004F88A0(Obj*, u32);
extern void func_004FAD90(Obj*);

void phase(Obj* p, s32 n) {
  func_004FC07C(p, n, -1, 0);
  if (p->child) func_002228D0(p->child, n, -1);
  func_004F88A0(p, p->f91c);
  func_004FAD90(p);
}

extern "C" void target(Obj* p) { phase(p, 12); }
