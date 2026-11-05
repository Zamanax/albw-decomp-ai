

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

extern "C" void* func_002D55D0(void*, int);
bool func_00291520(char* self, void* a1, f32 f) {
    if (*(u16*)(self + 0x42) != 0x45) goto fail5;
    char* r = (char*)func_002D55D0(*(void**)(self + 0x48), 0x17);
    if (!r) goto fail5;
    *(void**)r = a1;
    *(f32*)(r + 4) = f;
    *(u8*)(r + 8) = 0;
    *(u8*)(r + 9) = 0;
    *(u8*)(r + 0xa) = 1;
    *(f32*)(*(char**)(self + 0x18) + 0xfc) = 1.0f;
    return 1;
fail5:return 0;
}
