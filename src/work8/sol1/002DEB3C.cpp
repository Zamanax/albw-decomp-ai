

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

void* func_0049F688(void* list);
void func_0010F1DC(void* list, void* node);
u32 func_002DEB3C(char* self) {
    if (*(u32*)(self + 0x1c) == 0) return 0;
    char* obj; char* l2;
    char* l1 = self + 0x14;
    char* front = (char*)func_0049F688(l1);
    if (front == 0) goto fail;
    obj = front - *(u32*)(l1 + 0xc);
    if (obj == 0) goto fail;
    l2 = self + 0x24;
    func_0010F1DC(l2, *(u32*)(l2 + 0xc) + obj);
    *(u32*)(l2 + 8) += 1;
    return (u32)obj;
fail: return 0;
}
