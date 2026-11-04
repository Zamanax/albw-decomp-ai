typedef unsigned int u32;
typedef int s32;

#include "vec3.h"

extern "C" void func_002DFF7C(void*);
extern "C" u32 func_0019B04C(u32);
extern "C" void func_004C43E0(void*, void*);
extern "C" void func_00115C54(Vec3*, const Vec3*, const Vec3*);
extern u32 ro_0069330C;
extern Vec3 bss_0076F6C8;
extern void* data_00706E20;
void func_0023B228(char* self) {
    char buf[0x2c4];
    Vec3 t;
    u32 cnt = *(u32*)(self + 0x478) + 1;
    *(u32*)(self + 0x478) = cnt;
    if ((s32)cnt < 3) return;
    s32 n = 30 - (s32)*(u32*)(self + 0x474);
    *(u32*)(self + 0x478) = 0;
    if (n <= 0) return;
    *(u32*)(buf + 0x20) = 0; *(u32*)(buf + 0x24) = 0; *(u32*)(buf + 0x1c) = 0;
    *(u32*)(buf + 0x48) = 0; *(u32*)(buf + 0x4c) = 0; *(u32*)(buf + 0x2c0) = 0;
    func_002DFF7C(buf);
    *(u32*)buf = func_0019B04C(ro_0069330C);
    func_00115C54(&t, (Vec3*)(self + 0x3d0), &bss_0076F6C8);
    *(Vec3*)(buf + 4) = t;
    *(u32*)(buf + 0x20) = *(u32*)(self + 0x3e8) + 0xc0000000;
    *(u32*)(buf + 0x4c) = *(u32*)(self + 0x2cc);
    func_004C43E0(data_00706E20, buf);
}
