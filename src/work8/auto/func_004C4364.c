#include "albw_types.h"

extern void func_0052FD7C(void* p, void* f, u32 a);
extern void func_004C45C4(void* p);
extern void func_004C4870(void);

void func_004C4364(u8* self) {
    func_0052FD7C(self + 0x3dbbc, (void*)func_004C4870, 0);
    func_004C45C4(self);
    *(u32*)(self + 0x3dbe8) = 0;
    *(u32*)(self + 0x3dbe4) = 0;
    {
        void* o = *(void**)(self + 0x18);
        if (o != 0) {
            void** vt = *(void***)o;
            ((void (*)(void*))vt[4])(o);
            *(u32*)(self + 0x18) = 0;
        }
    }
    {
        void* o = *(void**)(self + 0x1c);
        if (o != 0) {
            void** vt = *(void***)o;
            ((void (*)(void*))vt[4])(o);
            *(u32*)(self + 0x1c) = 0;
        }
    }
}
