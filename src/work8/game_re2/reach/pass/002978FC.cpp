

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef float f32;

#include "vec3.h"


#include "flags.h"

struct Word32 {
u32 v;
Word32(u32 n):v(n){
}
};


struct Interp {
void setTarget(s32 frames, f32 target);
u8 opaque[0x1c];
};

struct StateData {
u16 id,reserved2;
u8 flag;
u8 reserved5[3];
u32 value;
};
struct StateControl {
StateData* func_002D55D0(s32);
};
struct ArrayCounts {
s32 num,capacity;
};
struct ObjectNode {
ObjectNode*prev;
ObjectNode*next;
void*object;
};

#include "sead_container.h"

struct CounterPair {
u32 cur,max;
bool step(){
CounterPair c=*this;
if(c.cur<c.max){
cur=c.cur+1;
return true;
}
return false;
}
};
struct StateObject48 {
u8 pad[0x48];
StateControl* state;
};

struct StateSlot12 {
void* owner;
s8 mode,current,pending;
u8 unknown7,gate8,gate9,unknownA[2];
};
struct Primary {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual ~Primary();
};
struct Base_0010DA7C {
Base_0010DA7C(void*,s32);
virtual ~Base_0010DA7C();
u8 pad[0x10-4];
};
struct Mid:Base_0010DA7C {
Mid():Base_0010DA7C(0,3){}
};
struct D_006DA49C:Primary,Mid {
void*a;
void*b;
D_006DA49C(void*,void*);
virtual ~D_006DA49C();
};
D_006DA49C::D_006DA49C(void*x,void*y):a(x),b(y){
}
