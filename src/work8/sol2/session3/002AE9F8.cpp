

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

struct M34E { char pad[0x508]; s16 m508; };
struct S2AE9F8 { char pad[0x34]; M34E* m34; char pad2[0xa4-0x38]; s8 bA4; };
extern "C" void func_002B193C(S2AE9F8*, int, float);
extern "C" void func_002AED24(S2AE9F8*);
extern "C" void func_002B0D7C(S2AE9F8*,int,float,int,int);
void func_002AE9F8(S2AE9F8* self) {
    if (self->m34->m508 <= 0) { func_002B193C(self, 0x11, 1.05f); return; }
    func_002AED24(self);
    s8 a = self->bA4;
    func_002B0D7C(self,0x11,0.35f,0xf,a);
}
