typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Vec3 { f32 x, y, z; };
struct Pr2ACE { u32 a, b; };
extern "C" void func_002ADE0C(void*, u32);
extern "C" void func_004FBCC0(void*);
extern "C" void func_004FD0B4(void*);
extern "C" void func_002AD658(void*, s32, s32, s32, Pr2ACE);
extern const Vec3 data_007A9260;
void func_002ACE74(char* self, u32 arg) {
    func_002ADE0C(self, arg);
    func_004FBCC0(*(void**)(self + 0x34));
    Vec3* d = (Vec3*)(self + 0x70);
    const Vec3* s = &data_007A9260;
    d->x = s->x; d->y = s->y; d->z = s->z;
    if (arg != 0x1f) func_004FD0B4(*(void**)(self + 0x34));
    Pr2ACE t; t.b = 1; t.a = 0;
    func_002AD658(self, 2, (u8)arg, 0x1f, t);
}
