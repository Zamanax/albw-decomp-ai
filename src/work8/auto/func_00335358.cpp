#include "../../work7/ds6/ds6.h"


#include "sead_string.h"
namespace sead {

}

void func_00150A84(void* self, const sead::SafeString& s, s32 v);

void func_00335358(u8* self) {
    if (self[0x531] != 0) return;
    func_00150A84(self, sead::SafeString("SE_OBJ_FALL"), 0);
}
