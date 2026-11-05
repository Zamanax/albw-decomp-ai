typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);
extern "C" void func_0014E2A0(void*, u32, void*, u32, u32, u32);
extern "C" void func_0023F8D8(void*);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

struct Owner { u8 pad[0x40c]; StateMgr mMgr; u8 pad2[0x434 - 0x430]; u32 mF434; u8 pad3[0x43c - 0x438]; void func_0023F828(); };
void Owner::func_0023F828() {
    mMgr.exec();
    func_0014E2A0(this, mF434, (u8*)this + 0x43c, 0x4000, 0, 0);
    func_0023F8D8(this);
}
