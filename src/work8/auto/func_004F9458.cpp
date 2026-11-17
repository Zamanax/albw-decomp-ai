#include "albw_types.h"
#include "vec3.h"

extern "C" f32 func_00115DC8(Vec3* v);

struct Dst { unsigned char pad[0x24]; Vec3 v; };
struct Self { unsigned char pad[0x420]; Dst* m420; unsigned int m424; Dst* m428; };

extern "C" void func_004F9458(Self* self, Vec3* v) {
    if (self->m420 != 0) {
        Vec3 t = *v;
        t.y = 0.0f;
        func_00115DC8(&t);
        Dst* d = self->m420;
        d->v.x = t.x;
        d->v.y = t.y;
        d->v.z = t.z;
    }
    if (self->m428 != 0) {
        Vec3 t = *v;
        t.y = 0.0f;
        func_00115DC8(&t);
        Dst* d = self->m428;
        d->v.x = t.x;
        d->v.y = t.y;
        d->v.z = t.z;
    }
}
