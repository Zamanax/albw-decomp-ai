#include "../../work7/ds2/ds2.h"

extern "C" void func_003252B8(void*, s32, f32);

#include "sead_string.h"
namespace sead {

}
extern void func_00150A84(void*, const sead::SafeString&, s32);

void func_00335138(void* self) {
    char* p = (char*)self;
    *(s8*)(p + 0x4cc) = 0;
    *(s8*)(p + 0x531) = 0;
    func_003252B8(self, *(s8*)(p + 0x490), *(f32*)(p + 0x4a8));
    func_00150A84(self, sead::SafeString("SE_PushPullStatue_MOVE"), 0);
}
