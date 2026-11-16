typedef float (*FnF)(float);
extern FnF data_007A3578[];
typedef struct {
  float m0;
  unsigned int pad4;
  unsigned int m8;
  unsigned char mc;
  unsigned char md;
  unsigned int m10;
  float m14;
  float m18;
  unsigned char pad1c;
  unsigned char m1d;
} T0056F090;
float func_0056F090(T0056F090* self) {
  unsigned int idx;
  unsigned int lim;
  FnF fn;
  float s;
  if (self->m0 == 0.0f) return 0.0f;
  lim = self->m10;
  if (self->m8 > lim) return 0.0f;
  idx = self->md;
  fn = data_007A3578[idx];
  if (fn == 0) {
    s = 1.0f;
  } else if (idx != 4) {
    s = fn(self->m14);
  } else if (self->m1d != 0) {
    s = fn(self->m14);
    self->m18 = s;
  } else {
    s = self->m18;
  }
  float m0 = self->m0;
  float t = m0 * s;
  return (float)self->mc * t;
}
