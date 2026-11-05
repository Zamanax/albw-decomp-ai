typedef unsigned int u32; typedef unsigned short u16; typedef signed char s8; typedef unsigned char u8; typedef float f32;
struct Base { virtual void v(); };
typedef void (Base::*PMF)();
extern "C" void func_00352210(void*, u32, f32);
extern "C" void func_00547514(void*);
extern "C" void func_00151214(void*);

#include "statemgr.h"
typedef StateMgrT<Base> StateMgr;

struct Owner {
    u8 pad0[0x2c]; u16 mFlag2c; u8 pad1[0x2d7 - 0x2e]; u8 mFlag2d7; u8 pad2[0x4f8 - 0x2d8];
    StateMgr mMgr; u8 pad3[0x588 - 0x51c]; u8 mFlag588;
    void func_00191208();
};
void Owner::func_00191208() {
    if (mFlag588) {
        if (mFlag2c == 1) func_00547514((u8*)this + 4);
        mFlag2d7 = 1;
        return;
    }
    mMgr.exec();
    func_00151214(this);
}
