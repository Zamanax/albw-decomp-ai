

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

struct Obj424 { char pad[0x2c]; u32 m2C; };
struct S26562C { char pad[0x424]; Obj424* m424; char p1[0x574-0x428]; f32 m574; char p2[0x8F4-0x578]; u32 m904; char p3[0x914-0x908]; u32 m910; };
extern "C" void func_004FABDC(void*, int, int, int);
extern "C" void func_004F88A0(void*, u32);
void func_0026562C(S26562C* self) {
    func_004FABDC(self, 0, -1, 0);
    func_004F88A0(self, self->m910);
    Obj424* o = self->m424;
    ((Flag32*)&o->m2C)->set(0x20000);
     self->m904 = 0;
    self->m574 = 0.5f;
}
