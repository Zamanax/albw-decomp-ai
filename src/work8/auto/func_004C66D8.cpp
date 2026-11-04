typedef unsigned int u32; typedef int s32; typedef float f32;
struct Vec3 { f32 x, y, z; };
struct Player { char pad0[0x1c]; Vec3* m1c; };
extern "C" {
extern void* data_0070B728;
extern Player* data_0070FB60;
s32 func_00584B94(void*, s32);
void func_004CDF40(void*, s32, s32);
}
extern "C" void func_004C66D8(void*, const Vec3* v) {
    if (func_00584B94(data_0070B728, 0x385) != 0)
        return;
    Player* p = data_0070FB60;
    Vec3* q = p->m1c;
    f32 dx = v->x - q->x;
    f32 dz = v->z - q->z;
    f32 d = dx * dx + dz * dz;
    if (d > 25.0f)
        return;
    func_004CDF40(data_0070B728, 0x385, 1);
}
