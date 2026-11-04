typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Obj43D { char pad0[0x158]; void* child; char pad15c[0x1a]; u8 flag; };
struct Vec2f { f32 x; f32 y; };
extern void func_0047A5B4(void*, Vec2f*, u32);
void func_0043D904(Obj43D* self) {
    Vec2f v;
    v.x = 94.0f;
    v.y = -108.0f;
    u32 b;
    if (self->flag & 1) b = 1; else b = 0;
    func_0047A5B4(self->child, &v, b);
}
