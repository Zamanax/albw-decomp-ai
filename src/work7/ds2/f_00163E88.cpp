#include "ds2.h"

extern void func_004FABDC(void*, int, int, int);

#include "sead_string.h"
namespace sead {

}
extern void func_00150A84(void*, const sead::SafeString&, s32);

void func_00163E88(void* self) {
    func_004FABDC(self, 7, -1, 0);
    func_00150A84(self, "SE_Omugai_APPEAR", 0);
}
