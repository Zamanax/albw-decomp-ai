#include "../../work7/ds3/ds3.h"
struct S2862 {
    char p0[0x3dc];
    f32 f3DC, f3E0, f3E4;
    char p3e8[0x4fc - 0x3e8];
    s32 m4fc;
    char p500[0x800 - 0x500];
    char p800[0x8e0 - 0x800];
    Vec3 m8e0;
    char p8ec[0x8f0 - 0x8ec];
    f32 f8f0;
};
struct S800 { char pad[0xf0]; f32 f0; };
extern "C" void func_004FC07C(void*, s32, s32, s32);
void func_0012411C(S2862* p) {
    p->f3DC = 0.0f; p->f3E0 = 0.0f; p->f3E4 = 0.0f;
    p->m4fc = 0;
    func_004FC07C(p, 0, -1, 0);
    Vec3* v = &p->m8e0;
    float sq = v->x * v->x + v->z * v->z;
    float t = sq * 0.006f;
    f32 lim = 0.04f; if (t > lim) t = lim;
    ((S800*)((char*)p + 0x800))->f0 = t;
}
