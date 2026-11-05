#include "../fam_rtti/rtti_cpp.h"
struct Vec3 { f32 x; f32 y; f32 z; };
struct A : Base { SEAD_RTTI_OVERRIDE(A, Base) u8 pad[0x2e - 4]; s16 m2E; u8 pad2[0x3d0 - 0x30]; Vec3 m3D0; };
struct Q { u8 pad[0x30]; Vec3* m30; };
struct Mgr { u8 pad[0x3dbc0]; Base** m3DBC0; u8 pad2[4]; Base** m3DBC8; };
extern "C" Mgr* data_00706E20;
extern "C" const u32 ro_006935FC;
extern "C" Base** func_005841A8(Mgr* mgr, u32 k, Base** from);
A* func_003A5CFC(Q* q, s32 id);
A* func_003A5CFC(Q* q, u32 id)
{
    f32 bestD = 9999.9f;
    A* best = 0;
    Mgr* g = data_00706E20;
    int k = ro_006935FC;
    Base** it = func_005841A8(g, k, g->m3DBC0);
    Base** end = data_00706E20->m3DBC8;
    for (; it != end;) {
        A* a = DynamicCast<A>(*it);
        if (a) { A * t0 = a;
if (t0->m2E == id) {
            if (0 == best || (q->m30->x - t0->m3D0.x) * (q->m30->x - t0->m3D0.x) + (q->m30->y - t0->m3D0.y) * (q->m30->y - t0->m3D0.y) + (q->m30->z - t0->m3D0.z) * (q->m30->z - t0->m3D0.z) < bestD) {
                best = t0;
                Vec3* c = &a->m3D0;
                f32 dy = q->m30->y - c->y;
                f32 dz = q->m30->z - c->z;
                f32 dx = q->m30->x - c->x;
                bestD = dx * dx + dy * dy + dz * dz;
            }
        } }
        it = func_005841A8(data_00706E20, ro_006935FC, it + 1);
    }
    return best;
}
