typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

struct Owner { u8 pad[0x40c]; StateMgr mMgr; void* m430; void* m434; void func_0050FD14(); };
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
void Owner::func_0050FD14() { Owner* self = this; self->mMgr.exec(); Owner* s2 = this; func_00169A80(s2->m434); func_00168E9C(s2->m434, s2->m430, 0); func_004CEAF0(s2->m430); }
