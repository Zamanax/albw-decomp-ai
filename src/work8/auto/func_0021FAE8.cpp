typedef unsigned char u8;
typedef int s32;
typedef float f32;

extern void func_0065E398(void*, int);

struct Vec3F { f32 x, y, z; };

struct Obj21FAE8 {
    char pad0[0x3d0];
    f32 m3D0;
    f32 m3D4;
    f32 m3D8;
    char pad3dc[0xa14 - 0x3dc];
    Vec3F mA14;
    char padA20[0xafd - 0xa20];
    u8 mAFD;
};

void func_0021FAE8(Obj21FAE8* self) {
    Vec3F* p = &self->mA14;
    f32 dx = p->x - self->m3D0;
    f32 dz = p->z - self->m3D8;
    f32 d = dx * dx + dz * dz;
    if (*(s32*)&d < 0x3ca3d70a) {
        if (self->mAFD == 0) {
            func_0065E398((char*)self + 0x8c0, 0x12);
        } else {
            func_0065E398((char*)self + 0x8c0, 0x13);
        }
    }
}
