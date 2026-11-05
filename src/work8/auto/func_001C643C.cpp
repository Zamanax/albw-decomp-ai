#pragma once
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef float f32;
typedef double f64;
typedef unsigned long ulong;


#include "flags.h"



extern void func_0014F4EC(void*);
extern void func_00150688(void*, void*, u32);

#include "sead_string.h"
namespace sead {

}
extern void func_00150A84(void*, const sead::SafeString&, s32);
void func_001C643C(void* self) {
    func_0014F4EC(*(void**)((char*)self + 0x40c));
    func_00150688(self, (char*)self + 0x43c, *(u32*)((char*)self + 0x3a4));
    char* v = (char*)self + 0x4a4; 
    *(f32*)(v) = 0.0f;
    *(f32*)(v + 4) = 0.0f;
    *(f32*)(v + 8) = 0.0f;
    func_00150A84(self, sead::SafeString("SE_OBJ_RECOVER_FROM_ICE"), 0);
}
