#include "../../work7/gpt17/range.h"
struct Obj { u8 pad[0x4c]; f32 lo; f32 d; f32 pad2; f32 scale; f32 hi; };
void f_004098FC(int a, Obj* p, int b, f32* out, f32 v) {
  f32 r = 0.f;
  f32 lo = p->lo;
  f32 hi = p->hi;
  if (v > lo) {
    r = (v - lo) / p->d * p->scale;
    if (r > hi) r = hi;
  }
  *out = r;
}
