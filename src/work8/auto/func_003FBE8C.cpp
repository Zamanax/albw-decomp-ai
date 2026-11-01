typedef float f32;
struct Vec3 { f32 x, y, z; };
extern "C" float __sqrtf(float v);

int func_003FBE8C(Vec3* out, const Vec3* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;
    f32 l = x * x + y * y + z * z;
    if (l == 0.0f)
        return 0;
    f32 inv = 1.0f / __sqrtf(l);
    out->x = x * inv;
    out->y = y * inv;
    out->z = z * inv;
    return 1;
}
