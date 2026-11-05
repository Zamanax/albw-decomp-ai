

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Control2317 {
u16 current, max;
u32 pad4, param;
};




#include "vec3.h"



#include "flags.h"

struct Sub9ac {
char p[0xf4];
};
struct S267914 {
char pad[0x59c];
u32 m59c;
char pad2[0x9ac-0x5a0];
Sub9ac sub;
u8 bAA0;
};
extern "C" void* data_00711F50;
extern "C" u32 data_006934FC;
extern "C" void func_004E9CD4(void*);
extern "C" void func_0036C408(void*, u32);
extern "C" void func_0036BA20(void*);
template<class T0> inline void hlp0(T0 self) { self->m59c |= 0x80; }
void func_00267914(S267914* self) {
    func_004E9CD4(data_00711F50);
    func_0036C408(&self->sub, data_006934FC);
    func_0036BA20(&self->sub);
    self->bAA0 = 0;

     hlp0(self);
}
