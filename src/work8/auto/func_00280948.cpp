struct Mid {
    unsigned char q[0x58];
    float v[3];
    unsigned char r[0x4];
    float b;
};
struct Obj {
    unsigned char p0[0x3d4];
    float a;
    unsigned char p1[0x400 - 0x3d8];
    Mid m;
};
static inline float divBy(float x, float y) { return x / y; }
static inline float mulBy(float a, float b) { return a * b; }
static inline float remap(float d) {
    float lo = 0.0f;
    float hi = 5.0f;
    float base = 1.0f;
    float top = 1.2f;
    if (d <= lo) return base;
    if (d >= hi) return top;
    return divBy(mulBy(0.20000005f, d - lo), hi) + base;
}

void func_00280948(Obj* p) {
    float d = p->a - p->m.b;
    float* v = p->m.v;
    float t = remap(d);
    v[0] = t;
    v[1] = t;
    v[2] = t;
}
