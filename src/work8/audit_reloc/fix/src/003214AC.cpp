

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

namespace sead{template<class T>struct SafeStringBase{virtual~SafeStringBase(){}virtual void assureTerminationImpl_()const{}const T*text;SafeStringBase(const T*s):text(s){}};}typedef sead::SafeStringBase<char>SafeString3b;
extern "C" char ro_006F5988[];
extern "C" const char* data_00711FB0;
extern "C" void* data_00711F50;
extern "C" void func_002944C4(void*, const SafeString3b*);
void func_003214F4(void* self, u32 flag) {
    if (flag) return;
    const SafeString3b&s=SafeString3b(data_00711FB0);
    
    
    func_002944C4(data_00711F50, &s);
}
