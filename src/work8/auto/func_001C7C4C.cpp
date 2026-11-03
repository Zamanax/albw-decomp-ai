typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef float f32;
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
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
extern "C" void func_0065C088(void*, u32);
struct T {
    char pad0[0x428];
    void* m428;
    AnimArr* m42c;
    char m430[0x10];
};
extern "C" void func_001C7C4C(T* t) {
    T* const s = t;
    func_00169A80(s->m42c);
    func_00168E9C(s->m42c, s->m428, 0);
    func_004CEAF0(s->m428);
    AnimArr* a = t->m42c;
    AnimElem& e = (*a)[0];
    if (!e.m1c && e.isEnd()) {
        func_0065C088(t->m430, 0);
    }
}
