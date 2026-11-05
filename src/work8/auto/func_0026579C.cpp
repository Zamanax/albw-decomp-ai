typedef unsigned int u32; typedef int s32; typedef float f32;

#include "sead_math.h"

extern const SinCosSample ro_006C3AB8[];
struct Parts { u32 low; u32 high; f32 r; const SinCosSample* table;
  Parts(const u32& idx) : low(idx & 0xffffff), high(idx >> 24), r((f32)low * (1.0f / 0x1000000)), table(ro_006C3AB8) {}
  f32 get() const { const SinCosSample& s = table[high]; return s.sin_val + s.sin_delta * r; } };
static inline s32 toFix(f32 v) { return (s32)(v * 1073741824.0f); }
f32 func_00153528(f32 a, f32 b, f32 x, f32 x0, f32 x1) {
    f32 u = (x - x0) / (x1 - x0);
    s32 v = toFix(u);
    Parts p((u32)v);
    f32 c = p.get();
    return b + (a - b) * c;
}
