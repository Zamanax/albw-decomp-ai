#include "ds2.h"


#include "sead_string.h"
namespace sead {

}
extern void func_00658B14(void*, int);
extern void func_00150A84(void*, const sead::SafeString&, s32);

u32 func_00173F4C(void* self) {
    if (*(u8*)((char*)self + 0x41c) != 0) return 0;
    func_00658B14((char*)self + 0x418, 1);
    func_00150A84(self, "SE_EyeStand_ON", 0);
    return 1;
}
