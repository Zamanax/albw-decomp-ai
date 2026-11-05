typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

struct T { u8 p0[0x420]; StateMgr sm; void* m444; u8 p448[0x458-0x448]; void* m458; };
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_00193918(T*);
extern "C" void func_00193880(T* self) {
    StateMgr* s = &self->sm;
    s->exec();
    T* o = self;
    func_00169A80(o->m444);
    func_00168E9C(o->m444, o->m458, 0);
    func_00193918(self);
}
