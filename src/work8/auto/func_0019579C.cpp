#include "albw_types.h"

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
bool func_005211BC(void* e, f32 a, f32 b);
s32 func_00588BF0(void* e, s32 a);
void func_00659A54(void* p, u32 mode);

void func_0019579C(void* self) {
    char* base = (char*)self + 0x400;
    char* r5 = base + 0x1c;
    void* p = self;
    bool r;
    u32 t = *(u16*)((char*)self + 0x36);
    if (t != 0) r = func_00588BF0(p, 0) != 0;
    else r = func_005211BC(p, 4.0f, 0.0f);
    if (r) { func_00659A54(r5, 3); return; }
    AnimArr* a = *(AnimArr**)((char*)self + 0x410);
    AnimElem& e = (*a)[0];
    if (!e.m1c && e.isEnd()) func_00659A54(r5, 0);
}
