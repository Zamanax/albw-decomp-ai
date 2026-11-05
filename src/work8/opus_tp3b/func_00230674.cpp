

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

extern "C" void func_0010F1F8(void*);
struct V1 { virtual void call(); };
static void recycle5(char* head,char*& p){    while (p != head) {
        char* next = *(char**)(p + 4);
        func_0010F1F8(p);
        *(u32*)(head + 8) -= 1;
        s32 v = *(u32*)(head + 0xc);
        p -= 4;
        *(u32*)p = v;
        *(char**)(head + 0xc) = p;
        p = next;
    }
}
void func_002FCCB8(char* self) {

    char* head = self + 0x34;
    char* p = *(char**)(self + 0x38);
    recycle5(head,p);
    V1* o = (V1*)*(void**)(self + 0x18);
    if (o) o->call();
}
