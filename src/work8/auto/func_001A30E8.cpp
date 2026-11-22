#include "albw_types.h"
extern "C" void func_004F9554(void*, int, int, int);
extern "C" void func_004F88A0(void*, u32);
extern "C" void func_0065A474(void*, int);

struct Pair984 { u32 a; u32 b; };

void func_001A30E8(char* self) {
    Pair984 c = *(Pair984*)(self + 0x984);
    if (c.a >= c.b) {
        func_004F9554(*(void**)(self + 0x964), 5, 4, 1);
        func_004F9554(*(void**)(self + 0x430), 5, 4, 1);
        func_004F9554(*(void**)(self + 0x434), 5, 4, 1);
        func_004F88A0(self, *(u32*)(self + 0x8e0));
    }
    if (*(u8*)(*(char**)(self + 0x510) + 4) != 0) {
        return;
    }
    s16 v = *(s16*)(self + 0x508);
    if (v > 0) {
        Pair984 d = *(Pair984*)(self + 0x984);
        if (d.a >= d.b) {
            func_0065A474(self + 0x8bc, 3);
        } else {
            func_0065A474(self + 0x8bc, 2);
        }
    } else {
        func_0065A474(self + 0x8bc, 6);
    }
}
