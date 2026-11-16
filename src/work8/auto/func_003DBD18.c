typedef unsigned int u32;
typedef int s32;
typedef struct Cfg { u32 a; u32 b; u32 c; } Cfg;
typedef struct Obj { u32 m0; u32 m4; u32 m8; u32 m0c; u32 m10; Cfg* m14; } Obj;
extern Cfg data_00716150;

u32 func_003DBD18(Obj* o)
{
    s32 t2;
    s32 t1;
    Cfg* p;
    u32 base;
    t1 = (s32)((o->m0 * 1000u) / 4888u);
    if (t1 < 1) t1 = 1;
    t2 = (s32)((o->m8 * 1000u) / 4888u);
    if (t2 < 1) t2 = 1;
    if (o->m14 != 0) { p = o->m14; } else { p = &data_00716150; }
    Cfg * t0 = p;
    base = t0->a + t0->b + t0->c;
    return (base + (5u * (u32)(t1 + t2) << 5)) << 3;
}
