typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
struct Vec3 { f32 x, y, z; };
struct Player { char pad0[0x1c]; Vec3* m1c; };
struct C;
extern Player* data_0070FB60;
s32 func_0053F480(Player* p);
s32 func_00556E64(Player* p);
Vec3* func_00520FC0(C* self);
void func_0065B158(s32* self, s32 v);
struct C {
    char pad0[0x3d0];
    Vec3 m3d0;
    char pad1[0x8bc - 0x3dc];
    s32 m8bc;
    char pad2[0x918 - 0x8c0];
    u16 m918;
    bool near();
    void f();
};
bool C::near() {
    if (m918 < 0x14)
        return false;
    Player* p = data_0070FB60;
    if (func_0053F480(p) == 0)
        return false;
    if (func_00556E64(p) != 0)
        return false;
    Vec3* pp = func_00520FC0(this);
    f32 dy = pp->y - m3d0.y;
    if (dy > 0.0f) {
    } else {
        dy = -dy;
    }
    if (!(dy < 2.0f))
        return false;
    Vec3* q = p->m1c;
    f32 dx = q->x - m3d0.x;
    f32 dz = q->z - m3d0.z;
    f32 d = dx * dx + dz * dz;
    return d < 12.25f;
}
void C::f() {
    if (near()) {
        func_0065B158(&m8bc, 4);
    } else if (m8bc == 0x5a) {
        func_0065B158(&m8bc, 2);
    }
}
