

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

struct Req5C4 { char p[0x5c]; };
struct S2F2474 { char pad[0x59c]; u32 m59C; char pad2[0xb7c-0x5a0]; u32 mB7C; char pad3[0xdb4-0xb80]; void* mDB4; char pad4[0xe0e-0xdb8]; u8 bE0E; };
extern "C" void func_002EEB98(S2F2474*);
extern "C" Req5C4* func_002C11E8(Req5C4*, int, int, int);
extern "C" void func_0016898C(void*, Req5C4*);
void func_002F2474(S2F2474* self) {
    self->bE0E = 1;
    func_002EEB98(self);
    ((Flag32*)&self->m59C)->reset(7);
    self->mB7C = 0;
    Req5C4 req;
    Req5C4* r = func_002C11E8(&req, 0, 0, 0);
    func_0016898C(self->mDB4, r);
}
