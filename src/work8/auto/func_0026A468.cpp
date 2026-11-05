#include "albw_types.h"

struct Vec3 { f32 x, y, z; };
struct SubX { bool func_0036BE48(); };
struct StateX { char p0[8]; };

struct En;
bool func_00521060(En* e);
void func_00660718(StateX* s, s32 v);

struct En {
    char p0[0x3d0];
    Vec3 m3d0;      // 0x3d0
    Vec3 m3dc;      // 0x3dc
    char p3e8[0x8c8 - 0x3e8];
    StateX mS8c8;   // 0x8c8
    char p8d0[0x9ac - 0x8d0];
    SubX m9ac;      // 0x9ac
    bool absOver() {
        f32 a = m3dc.y;
        a = (a > 0.0f) ? a : -a;
        f32 t0 = m3d0.y;
        return a > t0;
    }
    void f();
};

void En::f() {
    m9ac.func_0036BE48();
    if (func_00521060(this) || absOver()) {
        m3dc.x = 0.0f;
        m3dc.y = 0.0f;
        m3dc.z = 0.0f;
        m3d0.y = 0.0f;
        func_00660718(&mS8c8, 0x12);
    }
}
