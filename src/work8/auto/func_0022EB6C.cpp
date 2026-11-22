#include "vec3.h"
#include "albw_types.h"

struct W {
    Vec3 v;
    f32 m0c;
    f32 m10;
    s32 m14;
    s32 m18;
};

struct Obj {
    u8 pad0[0x3d0];
    Vec3 m3d0;
    u8 pad1[0x3e8 - 0x3dc];
    s32 m3e8;
    u8 pad2[0xa48 - 0x3ec];
    s32 ma48;
    u8 pad3[0xa68 - 0xa4c];
    W* ma68;
    u8 pad4[0xa6d - 0xa6c];
    u8 ma6d;
    u8 pad5[0xa70 - 0xa6e];
    Vec3 ma70;
};

extern "C" void func_004FABDC(Obj* e, s32 a, s32 b, s32 c);
extern "C" Vec3* func_00520FC0(Obj* e);
extern "C" void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);
extern "C" s32 func_0068C690(const Vec3& v);

void func_0022EB6C(Obj* self) {
    func_004FABDC(self, 3, -1, 0);
    Obj* o = self;
    u8 fl = self->ma6d;
    Vec3* src = fl ? func_00520FC0(o) : &o->ma70;
    Vec3 d = *src - self->m3d0;
    s32 angle = func_0068C690(d);
    self->ma48 = angle;
    W* p = self->ma68;
    p->m14 = self->m3e8;
    p->m18 = angle;
    p->v.x = 0.0f;
    p->v.y = 1.0f;
    p->v.z = 0.059999995f;
    p->m10 = 0.0f;
    p->m0c = 0.0f;
    W* q = self->ma68;
    q->m10 = q->v.x;
    q->m0c = 0.0f;
}
