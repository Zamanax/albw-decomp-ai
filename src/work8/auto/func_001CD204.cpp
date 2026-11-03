#include "../../work5/agent2/spawnparam_a2.h"
extern const u32 data_007844E4[];
u32 func_0019B04C(s32 id);
struct Mgr70C8E0;
extern Mgr70C8E0* data_0070C8E0;
s16 func_00581D60(Mgr70C8E0* m);
struct ActorMgr;
extern ActorMgr* data_00706E20;
void func_004C43E0(ActorMgr* m, const SpawnParam& p);
struct FlagHolder { char pad[0x2b4]; u32 flags; };
extern FlagHolder* data_0070D858;
extern u32 data_0070F3C8;
void func_001CD204(const Vec3& pos, u32 a, s32 arg2, s32 arg3) {
    if (a < 3) {
        SpawnParam p;
        p.m0 = func_0019B04C(data_007844E4[a]);
        if (arg3 >= 0)
            p.m50 = (s16)arg3;
        else
            p.m50 = func_00581D60(data_0070C8E0);
        p.m28 = (s16)arg2;
        p.m2a = (s16)a;
        p.m4.set(pos);
        p.m20 = 0;
        if (data_0070D858->flags & 8)
            p.m1c = data_0070F3C8;
        func_004C43E0(data_00706E20, p);
    }
}
