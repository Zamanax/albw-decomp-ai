

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
extern "C" void func_004EBA2C(void*, int, int);
extern "C" void func_00588C14(void*, int, int);
extern void* data_00711F50;
u32 func_0029F88C(char* self) {
    *(u8*)(self + 0x423) = 1;
    int c=func_00588BF0(self,0);
    char* r4=self+0x400;
    if(c==0){
        s16 a = *(s16*)(r4 + 0x24);
        if (a != 0 || *(u16*)(r4 + 0x26) != 0) {
            func_004EBA2C(data_00711F50, a, *(s16*)(r4 + 0x26));
        }
    }
    func_00588C14(self, 0, 1);
    if (*(u8*)(r4 + 0x22) == 0) *(u8*)(self + 0x2d7) = 1;
    return 0;
}
