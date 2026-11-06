#include "albw_types.h"
extern void* data_00706E20;
void target(char* p){
    char* m = *(char**)((char*)data_00706E20 + 0x3dbe8);
    u32* f = (u32*)(m + 0x10);
    if (*f != 0 && *f == *(u32*)(p + 0x2cc)) *f = 0;
    *(f32*)(p + 0x3dc) = 0.0f;
    *(f32*)(p + 0x3e0) = 0.0f;
    *(f32*)(p + 0x3e4) = 0.0f;
}
