

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

struct V24 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void s18(); virtual void s19(); virtual void v20(); virtual void v21();
    virtual void s22(); virtual void s23();
};
void func_002BF98C(char* self) {
    char* p = *(char**)(self + 0x14);
    ((Flag16*)(p+0x16))->reset(0x40);
    if (*(u8*)(self + 0x5e)) {
        if (*(u8*)(self + 0x5d)) ((V24*)self)->s23();
        else ((V24*)self)->s19();
        *(u8*)(self + 0x5f) = 1;
    } else {
        if (*(u8*)(self + 0x5d)) ((V24*)self)->s22();
        else ((V24*)self)->s18();
    }
}
