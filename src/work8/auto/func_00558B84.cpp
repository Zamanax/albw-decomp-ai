#include "../../work7/ds2/ds2.h"
u32 func_00588BE4(void*);
extern u32 ro_006937E0;
extern u32 ro_006937E4;

u32 func_00558B84(void* t, void* a) {
    if (func_00588BE4(a) == ro_006937E0) return 1;
    if (func_00588BE4(a) == ro_006937E4) return 1;
    void* obj = *(void**)((char*)t + 0x1c);
    void* ap = a;
    if (obj == 0) return 0;
    return (*(u32(**)(void*, void*))(*(u32*)obj))(obj, ap);
}
