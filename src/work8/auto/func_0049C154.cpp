struct Vec4 { float x, y, z, w; };
static inline float clampf(float v, float hi, float lo){ if (v < lo) return lo; if (v > hi) return hi; return v; }
void func_0049C154(Vec4* out, const Vec4* a, const Vec4* b, float t) {
    t = clampf(t, 1.0f, 0.0f);
    { float av = a->w; float bv = b->w; out->w = av + (bv - av) * t; }
    { float av = a->x; float bv = b->x; out->x = av + (bv - av) * t; }
    { float av = a->y; float bv = b->y; out->y = av + (bv - av) * t; }
    { float av = a->z; float bv = b->z; out->z = av + (bv - av) * t; }
}
