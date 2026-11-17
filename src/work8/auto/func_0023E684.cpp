typedef unsigned int u32;
typedef signed int s32;

struct Arr4 {
  u32 d[4];
  u32& at(u32 i) {
    if (i < 4) return d[i];
    return d[0];
  }
};

struct Sub {
  unsigned char pad[0x3b4];
  Arr4 arr;
};

struct Obj {
  unsigned char pad[0x400];
  Sub sub;
  u32 m7c4;
};

extern "C" void func_0014FD48(Obj* self);
extern "C" u32 func_00584E64(u32 p);
extern "C" u32 func_00584E70(u32 p);
extern "C" void func_004D0194(u32 p, u32 v);
extern "C" void func_004D0268(u32 p, u32 v);

extern "C" void func_0023E684(Obj* self) {
  func_0014FD48(self);
  for (s32 i = 0; i < 4; i++) {
    if (self->sub.arr.at(i) == self->m7c4) continue;
    u32& q = self->sub.arr.at(i);
    u32 a = func_00584E64(self->m7c4);
    func_004D0194(q, a);
    u32& r = self->sub.arr.at(i);
    u32 b = func_00584E70(self->m7c4);
    func_004D0268(r, b);
  }
}
