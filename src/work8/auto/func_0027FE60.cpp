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
extern "C" void func_00588C14(void* t, u32 a, u32 b);
extern "C" void func_00660F70(void* p, u32 n);
struct This27FE {
    char pad0[0x36];
    u16 m36;
    u16 m38;
    char pad1[0x4b4 - 0x3a];
    AnimArr* m4b4;
    char pad2[0x4bc - 0x4b8];
    s32 m4bc;
};

void func_0027FE60(This27FE* t) {
    if (t->m4bc == 6) {
        if (t->m36) func_00588C14(t, 0, 0);
        if (t->m38) func_00588C14(t, 1, 0);
    }
    if (t->m4bc >= 6) {
        AnimElem& e = (*t->m4b4)[0];
        if (!e.m1c && e.isEnd()) {
            func_00660F70(&t->m4bc, 3);
        }
    }
}
