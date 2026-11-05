

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

extern "C" f32 func_004F898C();
extern "C" void func_004F8964(f32*, int, f32);
extern "C" int func_0051D50C(void*);
extern "C" void func_004ED46C(void*, int);
extern "C" void func_002694A4(void*, int);
extern "C" void func_0035B084(int);
extern "C" int func_0058A8F0(void*);
extern "C" void func_00660718(void*, int) ;
extern void* data_00708998;
void func_0026A1F8(char* self) {
    f32 g = func_004F898C();
    func_004F8964((f32*)(self + 0x3e0), 1, g);
    if (func_0051D50C(data_00708998) == 0) func_004ED46C(data_00708998, 2);
    if (*(s32*)(self + 0x8c8) > 0x18) {
        func_002694A4(self, 1);
        func_0035B084(1);
    }
    if (func_0058A8F0(self) != 0) func_00660718(self + 0x8c8, 0);
}
