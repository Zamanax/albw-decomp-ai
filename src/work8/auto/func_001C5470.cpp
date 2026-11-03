typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned char u8;
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
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
};
struct AnimArr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
struct T1C5 {
    char pad0[0x7b0];
    void* m7b0;
    AnimArr* m7b4;
    void* m7b8;
    bool f();
};
bool T1C5::f() {
    func_00169A80(m7b4);
    AnimArr* a = m7b4;
    func_00168E9C(a, m7b0, 0);
    func_00169A80(m7b8);
    func_00168E9C(m7b8, m7b0, 0);
    func_004CEAF0(m7b0);
    AnimElem& e = (*m7b4)[0];
    if (!e.m1c) {
        if (e.m10 >= 0.0f) {
            if (e.m8 == e.m14) return true;
        } else {
            if (e.m8 <= 0.0f) return true;
        }
    }
    return false;
}
