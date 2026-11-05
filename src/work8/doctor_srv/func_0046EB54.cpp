

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
struct Vec2 {f32 x,y;};

#include "vec3.h"

struct Pair32 {u32 a,b;};
struct RangeNode19 {RangeNode19* prev;RangeNode19* next;};
struct CountedList19 {u32 count;RangeNode19 root;};
struct CriticalSection19 {u32 words[3];};

#include "flags.h"


struct Ctrl231 {s16 kind,index;u32 frame;void* owner;void init(void*,s16,s16);};
struct A{char pad[0xe];u8 flag;};struct G{char pad[0x90];A*values[4];};extern G*data_007142C8;struct S{char pad[0x90];u8 index;};extern void func_001B6C04(S*);
void impl(S*p,u32 i,G*g,u8 mode){u32 i_c2 = i;
A**a=g->values;if(i_c2<4)a+=i;(*a)->flag=mode;func_001B6C04(p);}
void f_0046EB54(S*p){impl(p,p->index,data_007142C8,3);}
