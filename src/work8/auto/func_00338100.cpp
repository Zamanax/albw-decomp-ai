typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned char u8;
extern "C" void func_00169A80(void*);
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
namespace sead {
class SafeString {
public:
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
}
void func_00150A84(void* self, const sead::SafeString& s, s32 v);
extern "C" void func_00665B80(void*, s32);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_00169A80(void*);
struct T338 {
    char pad0[0x40c];
    void* m40c;
    AnimArr* m410;
    char m414[0x10];
    void f();
};
void T338::f() {
    func_00169A80(m410);
    func_00168E9C(m410, m40c, 0);
    AnimElem& e = (*m410)[0];
    if (!e.m1c && e.isEnd()) {
        func_00665B80(m414, 2);
        func_00150A84(this, sead::SafeString("SE_SwitchSunlight_SHINE"), 0);
    }
}
