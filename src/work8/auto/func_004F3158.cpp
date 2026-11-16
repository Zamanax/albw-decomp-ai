#include "albw_types.h"
#include "sead_string.h"
#include "vec3.h"

extern char ro_00695114[];
extern char ro_0069511C[];

struct Anim344;
struct Eff { char p0[0x1c]; u32 m1c; };
struct EffHandle { Eff* p; u32 id; };
struct Self { char p0[0x344]; Anim344* m344; char p1[0x88]; Vec3 m3d0; };

EffHandle func_004A1B9C(Anim344* a, const char* name);
void func_004A2F38(Eff* e, const Vec3& pos);
void func_00150A84(Self* self, const sead::SafeString& name, s32 v);

void func_004F3158(Self* self) {
    Anim344* a = self->m344;
    const char* nm = ro_00695114;
    EffHandle h;
    h.p = 0;
    if (a != 0) {
        h = func_004A1B9C(a, nm);
    } else {
        h.id = 0;
    }
    Eff* e = h.p;
    const Vec3* pos = &self->m3d0;
    if (e != 0 && e->m1c == h.id) {
        func_004A2F38(e, *pos);
    }
    func_00150A84(self, sead::SafeString(ro_0069511C), 0);
}
