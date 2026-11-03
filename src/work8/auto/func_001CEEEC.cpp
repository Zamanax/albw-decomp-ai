typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

struct AnimElem {
    u32 m0, m4; f32 m8; u32 mC; f32 m10; f32 m14; u32 m18; u8 m1c; u8 pad1d[0x26 - 0x1d]; u8 m26;
    bool isEnd() const { if (m1c) return false; f32 z = 0.0f; if (m10 >= z) return m8 == m14; return m8 <= z; }
};
struct AnimArr {
    u32 pad[3]; s32 mNum; s32 mMax; AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
typedef AnimArr Ctl;
struct Model40C {
    char pad[0x158];
    f32 m158;
};
struct Obj1D8 {
    char pad0[0x2d7];
    u8 m2d7;
    char pad2d8[0x430 - 0x2d8];
    Model40C* m430;
    Ctl* m434;
    char pad438[0x448 - 0x438];
    f32 m448;
    void f();
};
// state exec: decay m430->m158 toward 0 by m448, clamp at 0; then set m2d7 when anim ends
void Obj1D8::f() {
    if (m430->m158 != 0.0f) {
        f32 v = m430->m158 - m448;
        if (v < 0.0f) v = 0.0f;
        m430->m158 = v;
    }
    if ((*m434)[0].isEnd()) m2d7 = 1;
}
