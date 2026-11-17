typedef unsigned int u32;
typedef int s32;
typedef struct Entry { u32 p0; u32 p1; u32 a; u32 b; } Entry;
typedef struct Table { u32 p0; u32 p1; u32 p2; s32 n; Entry* d; u32 base; } Table;

static inline Entry* tableAt(Table* t, s32 i)
{
  if ((u32)i < (u32)t->n) return t->d + i;
  return t->d;
}

u32 func_003FD944(Table* t, s32 i, u32* out)
{
  if (i < 0 || t->n <= i) return 0;
  u32 a = tableAt(t, i)->a;
  if (out != 0) {
    u32 b = tableAt(t, i)->b;
    if (a > b) return 0;
    out[1] = b - a;
    out[0] = a;
  }
  return t->base + a;
}
