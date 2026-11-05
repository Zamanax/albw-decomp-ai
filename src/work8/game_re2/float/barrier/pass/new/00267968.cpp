

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

struct S267968 { char pad[0x59c]; u32 m59c; };
extern "C" void* data_00708998;
extern "C" void func_004FABDC(void*, int, int, int);
extern "C" void func_004ED46C(void*, int);
extern "C" void func_0053A4CC(void*, void*, int);
template<class T0> inline void hlp0(T0 self) { self->m59c &= ~0x80; }
void func_00267968(S267968* self) {
    func_004FABDC(self, 6, -1, 0);
    func_004ED46C(data_00708998, 2);
    hlp0(self); 
    u8 buf[0x10];
    func_0053A4CC(self, buf, 0);
}
