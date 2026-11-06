#include "../../work5/agent10/en204.h"
extern Vec3 bss_007438A4;
void func_00163A30(En* e, s32 a);
void func_004F87F8(En* e, s32 a);
void func_004F8864(En* e, const Vec3& v, f32 t, u32 idx);
struct En2A : En {
    void f();
};
void En2A::f() {
    Vec3* v = &m4e4;
    v->set(0.95f, 0.95f, 0.95f);
    func_004FC07C(this, 0, -1, 0);
    func_00163A30(this, 1);
    m3dc.x = 0.0f;
    m3dc.z = 0.0f;
    ((Timer*)((0x800 + (char*)this) + 0x108))->start(randU32(func_0058A7D4(this), 150) + 30);
    func_004F87F8(this, 1);
    Vec3* g = &bss_007438A4;
    func_004F8864(this, *g, 0.6f, 0);
}
