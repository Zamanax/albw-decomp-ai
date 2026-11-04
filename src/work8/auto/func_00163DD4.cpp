#include "../../work7/ds3/ds3.h"
extern "C" void* func_0052FBA0(void*, u32);
extern "C" u32 func_00521184(void*);
extern "C" u32 func_0028AA74(void*);
extern "C" u32 func_004D80EC(void*, void*, u32);
extern void* data_00706E20;
u32 func_00163DD4(char* self, char* a1) {
    char* f = (char*)func_0052FBA0((char*)data_00706E20 + 0x3dbbc, *(u32*)(self + 0x8f8));
    if (f) {
        char* a = f;
        if (a1 != 0) {
            f32 dx = *(f32*)(a + 0x3d0) - *(f32*)(self + 0x3d0);
            f32 dz = *(f32*)(a + 0x3d8) - *(f32*)(self + 0x3d8);
            f32 d = dx * dx + dz * dz;
            if (d < 2.25f && func_0028AA74(a)) return 1;
        }
        *(u32*)(self + 0x904) = func_004D80EC(self + 0x3d0, a + 0x3d0, *(u32*)(self + 0x3e8));
        return 0;
    }
    *(u32*)(self + 0x904) = func_00521184(self);
    return 0;
}
