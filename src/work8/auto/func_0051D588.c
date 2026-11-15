typedef float f32;
typedef struct { f32 x, y, z; } Vec3L;
extern void func_00115CA8(Vec3L* out, const void* m, const Vec3L* v);
f32 func_0051D588(char* self, const Vec3L* v) {
    Vec3L t;
    Vec3L* o = &t;
    func_00115CA8(o, self + 0x118, v);
    return o->x * o->x + o->y * o->y;
}
