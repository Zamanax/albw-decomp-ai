typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
struct Pair { void* a; void* b; void upd(){ func_00169A80(b); func_00168E9C(b, a, 0); func_004CEAF0(a); } };
struct Owner { u8 pad[0x428]; Pair m428; StateMgr mMgr; void func_0050FD14(); };
void Owner::func_0050FD14() { mMgr.exec(); m428.upd(); }
