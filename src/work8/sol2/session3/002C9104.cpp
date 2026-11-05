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

extern "C" int func_00588BF0(void*, int);
extern "C" void func_00588C14(void*, int, int);
extern "C" void func_00663578(void*, int);
extern "C" void func_00150A84(void*,const SafeString&,int);

void func_002C9104(char* self) {
    if (func_00588BF0(self, 0) != 0) func_00588C14(self, 0, 0);
    func_00663578(self + 0x40c, 0);
    func_00150A84(self,SafeString("SE_SwitchCandle_OFF"),0);
}
