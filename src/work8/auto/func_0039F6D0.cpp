#include "albw_types.h"
#include "sead_string.h"
struct AnimElem {
    u32 m0, m4;
    f32 m8;
    u32 mC;
    f32 m10, m14;
    u32 m18;
    u8 m1c;
    u8 pad[0x26 - 0x1d];
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
struct Req5C { u32 m[0x5C / 4]; };
struct This39 { char pad0[4]; void* m4; char pad1[0x1c - 8]; AnimArr* m1c; };
struct SoundMgr { void playSE(const sead::SafeString& name, s32 a); };  // 0x4EA104
extern SoundMgr* data_00711F50;
void func_004CEA18(void*, u32, u32);
void func_0016898C(void*, const Req5C&);
void func_00169A80(void*);
extern "C" Req5C* func_002C11E8(Req5C*, int, int, int);

void func_0039F190(This39* t) {
    func_004CEA18(t->m4, 1, 1);
    Req5C req;
    Req5C* r = func_002C11E8(&req, 0, 10, 0);
    func_0016898C(t->m1c, *r);
    (*t->m1c)[0].m10 = 0.0f;
    (*t->m1c)[0].setFrame(1.0f);
    func_00169A80(t->m1c);
    data_00711F50->playSE(sead::SafeString("SE_PL_DRINK"), 0);
}
