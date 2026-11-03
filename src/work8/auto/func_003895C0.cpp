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
struct Sub3895 {
    char pad0[0x164];
    u32 m164;
};
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004D8AEC(void*, u32, void*);
extern "C" void func_004CEAF0(void*);
extern "C" void func_00667DD0(void*, u32);
struct T3895 {
    char pad0[0x3d0];
    char m3d0[0x3e8 - 0x3d0];
    u32 m3e8;
    char pad1[0x40c - 0x3ec];
    char m40c[0x460 - 0x40c];
    void* m460;
    AnimArr* m464;
    void f();
};
void T3895::f() {
    Sub3895* s = (Sub3895*)m460;
    s->m164 = s->m164 | 0x40000000;
    func_004D8AEC((char*)s + 0x80, m3e8, (char*)this + 0x3d0);
    func_00169A80(m464);
    func_00168E9C(m464, m460, 0);
    AnimArr* a = m464;
    AnimElem& e = (*a)[0];
    if (!e.m1c && e.isEnd()) {
        func_00667DD0((char*)this + 0x40c, 1);
    }
    return func_004CEAF0(m460);
}
