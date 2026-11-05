typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

struct Owner { u8 pad[0x960]; StateMgr mMgr; void func_0050FD14(); };
extern "C" void func_004BC8D8(Owner*);
void Owner::func_0050FD14() { mMgr.exec(); func_004BC8D8(this); }
