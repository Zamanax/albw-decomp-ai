typedef unsigned int u32;
extern void* data_00711F50;
extern "C" void func_00440CE4(void*);
extern "C" void func_00587F74(void*, void*, void*);
extern "C" void func_004EC690(void*, u32, u32);
#include "sead_string.h"

extern "C" void func_00486BF8(void* self) {
    func_00440CE4(self);
    const sead::SafeString& snd = sead::SafeString("SE_S_BOARD_START");
    func_00587F74(data_00711F50, (void*)&snd, 0);
    func_004EC690(data_00711F50, 0, 0);
}
