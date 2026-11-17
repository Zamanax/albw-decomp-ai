typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

extern void func_002B0D7C(void*,s32,f32,s32,s32);

struct Sub { char pad[0x895]; u8 mode; };
struct Obj { char pad[0x34]; struct Sub* sub; };

void func_002AEA54(struct Obj* o) {
    u8 m = o->sub->mode;
    f32 f = 0.3f;
    switch (m) {
    case 1:
    case 5: f = 0.0f; break;
    case 4: f = 0.15f; break;
    default: break;
    }
    func_002B0D7C(o, 18, f, 12, 0);
}
