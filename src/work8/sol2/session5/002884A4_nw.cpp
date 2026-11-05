

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

void func_00661480(void*,s32) ;
void func_002884A4(char* self) {
    *(f32*)(self + 0x3e0) = *(f32*)(self + 0x3e0) - 0.03f;
    if (*(f32*)(self + 0x3e0) <= 0.0f) func_00661480(self + 0x4dc, 2);
    if (*(u8*)(self + 0x424) != 0) {
        *(f32*)(self+0x3e0)=0.f;func_00661480(self+0x4dc,2);
    }
}
