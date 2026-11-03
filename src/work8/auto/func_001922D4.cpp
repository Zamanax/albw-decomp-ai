#include "../../work7/ds2/ds2.h"
struct AnimElem {
    u32 m0, m4;
    f32 m8;
    u32 mC;
    f32 m10;
    f32 m14;
    u32 m18;
    u8 m1c;
    u8 pad[0x26 - 0x1d];
    u8 m26;
    bool isEnd() const {
        bool end;
        if (m10 >= 0.0f) end = m8 == m14;
        else end = m8 <= 0.0f;
        return end;
    }
};
struct AnimArr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
extern "C" void func_00191C90(void*);
extern "C" void func_004A8304(void*, void*);
extern void* data_00709D28;
struct T1922D4 {
    char pad0[0x2d7];
    u8 m2d7;
    char pad1[0x40c - 0x2d8];
    void* m40c;
    char pad2a[0x418 - 0x410];
    s32 m418;
    char pad2[0x420 - 0x41c];
    AnimArr* m420;
    char pad3[0x425 - 0x424];
    u8 m425;
    char pad4[0x429 - 0x426];
    u8 m429;
    void f();
};
void T1922D4::f() {
    func_00191C90(this);
    m418 = m418 - 1;
    u8* b = (u8*)this + 0x400;
    if (m418 <= 0 && b[0x29] != 0) {
        func_004A8304(data_00709D28, m40c);
        m429 = 0;
    }
    if (b[0x25] != 0) {
        AnimElem& e = (*m420)[0];
        if (!e.m1c && e.isEnd()) {
            m2d7 = 1;
        }
    }
}
