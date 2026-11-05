#include "ds2.h"

extern void func_004FC07C(void*, int, int, int);

#include "sead_string.h"
namespace sead {

}
extern void func_00150A84(void*, const sead::SafeString&, s32);

void func_0015381C(void* self) {
    func_004FC07C(self, 4, -1, 0);
    func_00150A84(self, "SE_Bubble_BURN", 0);
}
