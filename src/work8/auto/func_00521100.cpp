typedef float f32;


#include "vec3.h"


struct PlayerPositionMgr { char pad0[0x1c]; Vec3* position; };
extern PlayerPositionMgr* data_0070FB60;

// 0x521100: the player's height relative to this object (its own Y offset by `y`)
// must lie inside the object's [bandMin, bandMax] window.
struct Object5211 {
    char pad0[0x3b0];
    f32 bandMin;
    f32 bandMax;
    char pad3b8[0x18];
    Vec3 position;
};

bool func_00521100(Object5211* o, f32 y) {
    PlayerPositionMgr* mgr = data_0070FB60;
    Vec3* pos = &o->position;
    f32 playerY = mgr->position->y;
    f32 height = playerY - (pos->y + y);
    return o->bandMin < height && height < o->bandMax;
}
