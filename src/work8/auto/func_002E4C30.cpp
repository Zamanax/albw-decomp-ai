#include "sead_string.h"

typedef unsigned int u32;
typedef int s32;

extern char ro_0069543C[];   // "Land"
extern char ro_00695444[];   // "SE_BigIceGimos_LAND"

struct Eff {
    char p0[0x1c];
    u32 m1c;
};

struct EffHandle {
    Eff* p;
    u32 id;
};

struct Anim344;

struct Vec3 {
    float x, y, z;
};

struct Self {
    char p0[0x344];
    Anim344* m344;
    char p1[0x3d0 - 0x348];
    Vec3 m3d0;
};

EffHandle func_004A1B9C(Anim344* a, const char* name);
void func_004A2F38(Eff* e, const Vec3& pos);
void func_00150A84(Self* e, const sead::SafeString& name, s32 v);

static void startEff(EffHandle* h, Anim344* a, const char* name) {
    if (!a) {
        h->p = 0;
        h->id = 0;
        return;
    }
    *h = func_004A1B9C(a, name);
}

void func_002E4C30(Self* self) {
    EffHandle h;
    startEff(&h, self->m344, ro_0069543C);
    Vec3* p = &self->m3d0;
    if (h.p && h.p->m1c == h.id) func_004A2F38(h.p, *p);
    func_00150A84(self, sead::SafeString(ro_00695444), 0);
}
