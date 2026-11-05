

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

extern "C" void func_00165E28(void*, int);
extern void* data_0070B728;
void func_00308110(char* self) {
    u32 n = *(u32*)(self + 0x564) + 1;
    *(u32*)(self + 0x564) = n;
    if (n <= 0xc8) return;
    char* g=(char*)data_0070B728;
    char* p = self + 0x458;
    char* q = *(char**)((char*)g + 0x44);
    if (q && q == p && *(u8*)(self + 0x550) == 0) func_00165E28(p, 0x3c);
    char*q2=*(char**)((char*)data_0070B728+0x44);
    if (q2 && q2 == p) return;
    *(u8*)(self + 0x2d7) = 1;
}
