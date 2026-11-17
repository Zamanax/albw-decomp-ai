#include "sead_string.h"

extern "C" void func_00440E38();
extern "C" void func_004EC8E8(void*);
extern "C" unsigned func_00587F74(unsigned, const sead::SafeString&, unsigned);
extern void* data_00711F50;

extern "C" void func_00486C5C() {
    func_00440E38();
    func_004EC8E8(data_00711F50);
    func_00587F74((unsigned)data_00711F50, sead::SafeString("SE_S_BOARD_END"), 0);
}
