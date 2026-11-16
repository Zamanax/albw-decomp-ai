typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef struct Ent { u32 base; f32 scale; } Ent;
extern const Ent ro_006C53D8[];
u32 func_004905E0(f32 t) {
    f32 x = t * 128.0f;
    s32 i = (s32)x;
    const Ent* e = &ro_006C53D8[i];
    return e->base + (u32)(e->scale * (x - (f32)i));
}
