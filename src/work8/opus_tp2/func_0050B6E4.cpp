typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
struct Owner { u8 pad[0x40c]; void* m40c; void* m410; StateMgr mMgr; void func_0050B6E4(); void tail(){ if (m410) { func_00169A80(m410); func_00168E9C(m410, m40c, 0); } } };

void Owner::func_0050B6E4() { mMgr.exec(); tail(); }
