typedef unsigned short u16;
typedef int s32;
typedef float f32;
typedef struct { f32 x, y, z; } Vec3;
typedef struct Obj {
    char pad0[0x2e];
    u16 m2e;
    char pad1[0x3a0];
    f32 x3d0;
    char pad2[4];
    f32 z3d8;
    char pad3[0xb0];
    s32 m48c;
} Obj;
typedef struct Player { char pad0[0x1c]; Vec3* m1c; } Player;
extern Player* data_0070FB60;
void func_002C81E8(Obj* self);

void func_002C816C(Obj* self) {
    if (self->m2e != 0) return;
    Player* p = data_0070FB60;
    Vec3* q = p->m1c;
    f32 dx = self->x3d0 - q->x;
    f32 dz = self->z3d8 - q->z;
    f32 d = dx * dx + dz * dz;
    if (d >= 25.0f) {
        self->m48c = 0;
        return;
    }
    self->m48c = self->m48c + 1;
    if (self->m48c > 40) func_002C81E8(self);
}
