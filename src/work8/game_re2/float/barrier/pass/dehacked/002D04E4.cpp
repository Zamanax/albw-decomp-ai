

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

extern "C" void func_00151148(void*, int);
extern "C" void func_004A3700(void*);
struct Handle5{char*p;u32 id;};
static void kill5(Handle5*h5){char*o=h5->p;if(o&&*(u32*)(o+0x1c)==h5->id){*(u32*)(o+0x3c)=(*(u32*)(o+0x3c)&~0x44)|8;func_004A3700(o);}}
template<class T0, class T1> inline void hlp1(T0 v, T1 self) { if (!v) {
        func_00151148(*(void**)(self + 0x44c), 1);
        *(f32*)(self + 0x3e0) = -0.5f;
    }
    *(f32*)(self + 0x3ac) = -1.0f; }
void func_002D04E4(char* self) {
    u32 v = *(s16*)(self + 0x30);
    *(u32*)(self + 0x4cc) = v;
    hlp1(v, self);
    Handle5*h5=(Handle5*)(self+0x4c4);kill5(h5);
}
