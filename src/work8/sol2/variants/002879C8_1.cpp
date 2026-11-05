

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

extern "C" void* func_0052FBA0(void*, u32);
extern void* data_00706E20;
int func_002879C8(char* self, char* a1) {
    u8*q=(u8*)(self+0x400);char* arg=a1;
    if (q[0x15]) goto done;
    if (!func_0052FBA0((char*)data_00706E20 + 0x3dbbc, *(u32*)(arg + 0x28))) goto done;
    char* p = *(char**)(arg + 0x2c);
    if (!p) goto done;
    if (*(u8*)(p + 3) != 1) goto done;
    *(u8*)(self + 0x415) = 1;
    if (q[0x24]) *(u8*)(self + 0x425) = 1;
    done:return 0;
}
