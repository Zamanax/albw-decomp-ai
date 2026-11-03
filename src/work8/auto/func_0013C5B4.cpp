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
void func_004CF478(void*, u32, u32);
void func_006572F8(void*, u32);
struct This2244 {
    char pad0[0x410];
    void* m410;
    AnimArr* m414;
    char pad1[0x43c - 0x418];
    u16 m43c;
};

void func_0013C5B4(This2244* t) {
    if (t->m43c != 0) {
        --t->m43c;
        if (t->m43c == 0) {
            func_004CF478(t->m410, 1, 0);
            (*t->m414)[0].m10 = 1.0f;
        }
    }
    AnimElem& e = (*t->m414)[0];
    if (!e.m1c && e.isEnd()) {
        func_006572F8((char*)t + 0x418, 0);
    }
}
