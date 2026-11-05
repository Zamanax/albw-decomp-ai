

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

extern "C" int func_0058AB74(void*);
extern "C" int func_0058A8F0(void*);
extern "C" void func_004FC07C(void*, int, int, int);
extern "C" void __attribute__((notailcall)) func_006640EC(void*, int);
struct Pair { u32 cur, max; };
bool step(Pair*q){Pair p = *q;if(p.cur < p.max){q->cur=p.cur+1;return true;}return false;}
void func_002F653C(char*self){if(step((Pair*)(self+0xb0c))){if(func_0058AB74(self)==0x25&&func_0058A8F0(self)!=0)func_004FC07C(self,0x24,-1,0);}else func_006640EC(self+0x8c8,0x20);}
