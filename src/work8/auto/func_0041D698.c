typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct Obj {
  u8 p0[4];
  float f4;
  u32 m8;
  u8 p0c[2];
  u8 m0e;
  u8 p0f;
  u32 m10;
  float f14;
  u8 p18[4];
  u8 m1c;
  u8 m1d;
} Obj;

void func_0041D698(Obj* o, s32 d)
{
  u32 cur = o->m10;
  u32 lim = o->m8;
  if (cur < lim) {
    u32 nc = cur + (u32)d;
    if (nc <= lim) {
      o->m10 = nc;
      return;
    }
    d = d - (s32)(lim - cur);
    o->m10 = lim;
  }
  if (o->f4 > 0.0f) {
    if (o->m1c == 0) {
      o->m1c = 1;
      o->f14 = (float)o->m0e * 0.00787401574f;
    }
    float s2 = (float)d * 0.001f;
    float acc = o->f14 + o->f4 * s2;
    s32 b = *(s32*)&acc;
    o->f14 = acc;
    if (b >= 0x3f800000) {
      o->m1d = 1;
    } else {
      o->m1d = 0;
    }
    acc = acc - (float)(s32)acc;
    o->f14 = acc;
  }
}
