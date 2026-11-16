#include "albw_types.h"
extern void* data_00712450;
u32 func_0014A354(void* a, u32 b);
void func_001031B4(void* a, void* b);
void func_0049DBDC(void* a, void* b);
void func_00688458(void);
void func_0014ADB4(u8* self) {
    u8 buf[0x8c];
    u32 r5 = func_0014A354(data_00712450, 0);
    void* fp = (void*)func_00688458;
    *(void**)(buf + 0x84) = fp;
    u8* p = buf + 0x80;
    *p = 2;
    func_001031B4(buf, p);
    *(void**)(buf + 0x70) = self + 0x1000 + 0xb0;
    *(u32*)(buf + 0x64) = r5;
    func_0049DBDC(*(void**)(self + 0x18), buf);
}
