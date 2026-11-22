#include "albw_types.h"
#include "sead_string.h"
struct Req5C { u8 raw[0x5C]; };
struct SoundMgr { void playSE(const sead::SafeString& name, s32 a); };
struct AnimElem {
    u32 m0, m4;
    f32 m8;
    u32 mC;
    f32 m10, m14;
    u32 m18;
    u8 m1c;
    u8 pad[9];
    u8 m26;
    void setFrame(f32 f) { if (m8 != f) { m8 = f; m26 = 1; } }
};
struct AnimArr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
struct ThisT { u32 m0; void* m4; char pad[0x14]; AnimArr* m1c; };
extern SoundMgr* data_00711F50;
extern "C" void func_004CEA18(void*, u32, u32);
extern "C" Req5C* func_002C11E8(Req5C*, int, int, int);
extern "C" void func_0016898C(void*, const Req5C&);
extern "C" void func_00169A80(void*);
void func_0039F3B0(ThisT* t) {
    func_004CEA18(t->m4, 1, 1);
    Req5C req;
    Req5C* r = func_002C11E8(&req, 0, 10, 0);
    func_0016898C(t->m1c, *r);
    (*t->m1c)[0].m10 = 0.0f;
    (*t->m1c)[0].setFrame(2.0f);
    func_00169A80(t->m1c);
    data_00711F50->playSE(sead::SafeString("SE_PL_DRINK"), 0);
}
