typedef float f32;
typedef unsigned int u32;
typedef struct Ent { f32 x, y, z; } Ent;
typedef struct S { f32 base; f32 step; u32 pad; Ent* tab; } S;
extern f32 func_00566F70(S*, Ent*, f32);
void func_0068FD18(S* p, Ent* out, f32 t)
{
  f32 v = func_00566F70(p, out, t) - p->base;
  u32 i = (u32)v;
  f32 frac = v - (f32)i;
  if (frac == 0.0f) {
    Ent* q = &p->tab[i];
    *out = *q;
    return;
  }
  if (p->step == v) {
    Ent* q = &p->tab[i + 1];
    *out = *q;
    return;
  }
  {
    Ent* a = &p->tab[i];
    Ent* b = &p->tab[i + 1];
    out->x = a->x + frac * (b->x - a->x);
    out->y = a->y + frac * (b->y - a->y);
    out->z = a->z + frac * (b->z - a->z);
  }
}
