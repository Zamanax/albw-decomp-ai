namespace sead{template<class T>struct SafeStringBase{virtual~SafeStringBase(){}virtual void assureTerminationImpl_()const{}const T*text;SafeStringBase(const T*s):text(s){}};typedef SafeStringBase<char> SafeString;}typedef sead::SafeString SafeString;


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

extern "C" void* func_0010B954(u32,const SafeString&,int,int,int);
extern "C" void func_0025B1B4(void*);

void func_0025B324(char* self) {
    if (*(u8*)(self + 0xd8)) return;
    void* r = func_0010B954(0x34800,SafeString("SoundFxHeap"),0,1,0);
    *(void**)(self + 0x64) = r;
    if (r) func_0025B1B4(self);
    *(u8*)(0xd8 + self) = 1;
}
