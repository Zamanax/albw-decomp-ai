#include "albw_types.h"
extern "C" {
extern u32 data_0070FB60;
extern u32 data_0070C968;
extern u32 data_00706E20;
extern void func_00437560();
extern void func_0052FD7C(void*, void (*)(), u32);
}
extern "C" void func_0027B0A8(u32 a) {
    u32 o = data_0070FB60;
    u32 v;
    if (o == 0) {
        v = 0;
    } else {
        v = *(u32*)(o + 0x2c);
        v = *(u32*)v;
    }
    data_0070C968 = v;
    u32 arg = a;
    char* g = (char*)data_00706E20;
    func_0052FD7C(g + 0x3dbbc, func_00437560, arg);
}
