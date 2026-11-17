typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

typedef struct Obj1D2 {
    u8 pad0[0x3dc];
    f32 m3DC;
    u8 pad1[0x3e4 - 0x3e0];
    f32 m3E4;
    u8 pad2[0x8bc - 0x3e8];
    u32 m8BC;
    u8 pad3[0x924 - 0x8c0];
    f32 m924;
    f32 m928;
    u8 pad4[0x930 - 0x92c];
    f32 m930;
} Obj1D2;

typedef struct Mid {
    u8 pad0[0x124];
    f32 a;
    f32 b;
    u8 pad1[4];
    f32 c;
} Mid;

extern void func_004FB4E0(Obj1D2* self, f32 v);
extern void func_0065E630(u32* p, u32 v);
void func_00223970(Obj1D2* self) {
    Mid* m = (Mid*)((u8*)self + 0x800);
    f32 t = m->a;
    t += (0.04f - t) * 0.08f;
    m->a = t;
    self->m3DC = m->b * t;
    self->m3E4 = m->c * t;
    t = t * 40.0f;
    f32 one = 1.0f;
    if (t > one) t = one;
    func_004FB4E0(self, t);
    if (self->m8BC >= 60u) func_0065E630(&self->m8BC, 0u);
}
