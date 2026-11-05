#include "albw_types.h"

#include "vec3.h"


#include "sead_math.h"

extern const SinCosSample ro_006C3AB8[];
inline void copyVec(Vec3* d, const Vec3& s) { *d = s; }
struct Parts { u32 low; u32 high; f32 r; const SinCosSample* table;
  Parts(const u32& idx) : low(idx & 0xffffff), high(idx >> 24), r((f32)low * (1.0f / 0x1000000)), table(ro_006C3AB8) {}
  f32 get() const { const SinCosSample& s = table[high]; return s.sin_val + s.sin_delta * r; } };
inline f32 sinIdx(const u32& idx) { Parts p(idx); return p.get(); }
struct En {
    char p0[0x4e4];
    Vec3 m4e4;
    char p4f0[0x9c4 - 0x4f0];
    s32 m9c4;
    void squash();
};
void En::squash() {
    if (m9c4 <= 0) return;
    m9c4--;
    f32 s = 1.0f;
    s32 n = m9c4;
    if (n >= 9 || n <= 0) {} else s = 1.0f + sinIdx((n % 3) * 0x55555488) * 0.03f;
    f32 inv = 1.0f / s;
    copyVec(&m4e4, Vec3(s, inv, s));
}
