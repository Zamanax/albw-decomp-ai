#include "sead_string.h"

extern "C" void* data_00711F50;
extern "C" void func_002DF0B0(void*, const SafeString&, int);
extern "C" void func_004E9840(void*);
extern "C" void func_0030B0F8(void*);

void func_003A52EC(void* self) {
    func_002DF0B0(data_00711F50, SafeString("SE_S_TELEPATHY"), 0);
    func_004E9840(data_00711F50);
    func_0030B0F8(self);
}
