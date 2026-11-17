struct P22AFB0 { unsigned int a; unsigned int b; };
struct Obj22AFB0 { char pad0[0xa70]; unsigned int a70; unsigned int a74; char pad1[0x23c]; int cb4; };
extern void func_00229E24(void*);
extern void func_0022AA1C(void*, int);
extern void func_0065E8B8(void*, int);

void func_0022AFB0(struct Obj22AFB0* self) {
  func_00229E24(self);
  struct P22AFB0 c = *(struct P22AFB0*)&self->a70;
  if (c.a < c.b) self->a70 = c.a + 1;
  if (self->cb4 >= 2 && self->a70 == 0x3c) {
    int v = self->cb4 / 2;
    int lo = 1;
    int hi = 3;
    if (v < lo) v = lo;
    else if (v > hi) v = hi;
    func_0022AA1C(self, v);
  }
  struct P22AFB0 d = *(struct P22AFB0*)&self->a70;
  if (d.a >= d.b) func_0065E8B8((char*)self + 0x8fc, 10);
}
