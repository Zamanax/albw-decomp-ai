

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

struct S31A110 { char pad[0x3d4]; f32 m3d4; char pad2[0x420-0x3d8]; s32 m420; char pad3[0x478-0x424]; f32 v478; char pad4[0x7c4-0x47c]; u8 b7C4; };
template<class T0> inline void hlp0(T0 p) { *p += (0.8f - *p) * 0.1f; }
void func_0031A110(S31A110* self) {
    if (0x14 < self->m420) { self->b7C4 = 1; return; }
    f32* p = &self->v478;
    hlp0(p); 
    self->m3d4 -= 0.2f;
}
