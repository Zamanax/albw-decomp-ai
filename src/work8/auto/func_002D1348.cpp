

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

struct Obj2D13 { char p[0x34]; };
struct S2D1348 { char pad[4]; };
extern "C" char ro_006DD678[];
extern "C" Obj2D13* func_0010DA7C(S2D1348*, int, int);
void func_002D1348(S2D1348* self, int a1, void* a2) {
    const Obj2D13* o = func_0010DA7C(self, 0, 3);
    *(void**)o = ro_006DD678;
    f32 ro_006DD678 = 0.0f;
    
    *(void**)((char*)o + 0x10) = a2; *(f32*)((char*)o + 0x14) = 0.0f;
    *(f32*)((char*)o + 0x18) = 0.0f;
    *(f32*)((char*)o + 0x1c) = 0.0f;
    *(f32*)((char*)o + 0x20) = 0.0f; 
    *(f32*)((char*)o + 0x24) = 0.0f;
    *(f32*)((char*)o + 0x28) = 0.0f; 
    *(u8*)((char*)o + 0x2c) = 0;
    *(u8*)((char*)o + 0x2d) = 0;
    *(u32*)((char*)o + 0x30) = 0;
}
