#define OBJ1D6_EXTRA void func_0035C8D0();
#include "../../work5/agent4/obj1d6.h"
struct Blk52C { u32 a; u32 b; f32 c; };
void Obj1D6::func_0035C8D0() {
    Blk52C& k = *(Blk52C*)&m52c;
    k.b = 0x77;
    k.c = 0.008403361774981022f;
    k.a = 0;
    playSE(sead::SafeString("SE_OBJ_FALL"), 0);
}
