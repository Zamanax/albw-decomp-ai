

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

extern "C" void func_0014E2A0(void*, void*, void*, int, void*, int);
extern "C" void func_004CEAF0(void*);
s32 clamp(s32 n,s32 lo){if(n<lo)n=lo;return n;}
void func_003097BC(char* self) {
    if (*(u8*)(self + 0x435)) return;
    s32 n=clamp(*(u32*)(self+0x430)-1,0);
    *(u32*)(self + 0x430) = n;
    func_0014E2A0(self, *(void**)(self + 0x41c), self + 0x438, 0x1008, 0, 0);
    func_0014E2A0(self, *(void**)(self + 0x418), self + 0x438, 0x200, self + 0x448, 0);
    func_004CEAF0(*(void**)(self + 0x40c));
}
