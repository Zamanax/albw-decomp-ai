

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Control2317 { u16 current, max; u32 pad4, param; };




#include "vec3.h"



#include "flags.h"

extern "C" void func_0014B1D4(void*, int, int);
extern "C" void func_00231C00(void*, void*);
extern void* data_00712F70;
void func_002FE72C(char* self) {
    if (*(u8*)(self + 0x50) != 2 || *(u8*)(self + 0x91) != 0) return;
    u8 a = *(u8*)(self + 0x92);
    u8 b = *(u8*)(self + 0x90);
    if (a == b) return;
    b = (u8)(b + 1);
    *(u8*)(self + 0x90) = b;
    if (b == a) func_0014B1D4(data_00712F70, 0, 1);
    u32 t[2];
    *(u8*)(self + 0x91) = 8;
    t[0] = *(u32*)(self + 0x84);
    t[1] = *(u32*)(self + 0x88);
    func_00231C00(self, t);
}
