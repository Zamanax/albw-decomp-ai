#include "statemgr.h"

extern "C" bool func_00542AE4(StateMgrBase* self, u32 k) {
    if (k < 0x21) {
        if (self->mCur == 0) return true;
        u32 cur = (u8)self->mCur;
        if (cur < 0x15) {
            if (k != 3) return true;
            if (cur > 3) return false;
            return true;
        }
    }
    return false;
}
