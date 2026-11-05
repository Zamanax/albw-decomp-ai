#include "albw_types.h"
#include "vec3.h"

// 0x00289FF0: gravity + step-reaction update of an actor.
//  The actor keeps a position Vec3 at 0x3D0, a velocity Vec3 at 0x3DC (its Y at 0x3E0)
//  and the state word handed to func_00661708 at 0x4F4.
//  0x00115C54 = Vec3::setAdd, 0x007A9260 = sead::Vector3f::zero, 0x0014EEC8 = step query
//  (out vec, offset vec, rate, id), 0x00661708 = state setter, 0x00520EE4 / 0x00520FF8 =
//  state tests, 0x00289F70 = default reaction.
extern const Vec3 data_007A9260;
extern "C" bool func_0014EEC8(void*, Vec3*, const Vec3*, f32, u32);
extern "C" bool func_00520EE4(void*);
extern "C" bool func_00520FF8(void*);
extern "C" void func_00661708(u32*, s32);
extern "C" void func_00289F70(void*);

struct Actor {
    char pad0[0x3d0];
    Vec3 pos;          // 0x3D0
    Vec3 vel;          // 0x3DC
    char pad1[0x18];
    char pad2[0xf4];
    u32 state;         // 0x4F4
};

extern "C" void func_00289FF0(Actor* self) {
    self->vel.y -= 0.0125f;
    {
        Vec3& pos = self->pos;
        pos.setAdd(pos, self->vel);
    }
    Vec3 tmp = data_007A9260;
    if (func_0014EEC8(self, &tmp, &data_007A9260, 0.1f, 0xddf)) {
        Vec3& pos = self->pos;
        pos.setAdd(pos, tmp);
        func_00661708(&self->state, 5);
    }
    if (func_00520EE4(self)) {
        func_00661708(&self->state, 8);
        return;
    }
    if (func_00520FF8(self)) {
        func_00661708(&self->state, 9);
        return;
    }
    func_00289F70(self);
}
