#include "actor.h"
#include "sead_string.h"
#include "albw_types.h"

extern "C" u32 func_00584B94(void* mgr, s32 id);
extern "C" void func_00150A84(ActorBase* self, const sead::SafeString& s, s32 n);
extern "C" void* data_0070B728;

extern "C" void func_00302F6C(ActorBase* self) {
    bool ok = func_00584B94(data_0070B728, 0x2c7) != 0 && func_00584B94(data_0070B728, 0x2c9) != 0 &&
              func_00584B94(data_0070B728, 0x2cb) != 0 && func_00584B94(data_0070B728, 0x2cd) != 0;
    *(u8*)((u8*)self + 0x4e8) = ok;
    if (ok) {
        func_00150A84(self, sead::SafeString("SE_DoorBossGanon_OPEN"), 0);
    }
}
