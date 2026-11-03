typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
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
};
struct AnimArr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
struct Flag {
    u8 pad[4];
    u8 m4;
};
struct This {
    char pad0[0x410];
    AnimArr* m410;
    char pad1[0x508 - 0x414];
    s16 m508;
    char pad2[0x510 - 0x50a];
    Flag* m510;
    char pad3[0x9d0 - 0x514];
    char m9d0[1];
    char pad4[0xa04 - 0x9d1];
    u8 ma04;
};
void func_001A094C(This*, u32);
void func_0065A330(void*, u32);

void func_0019FD08(This* t) {
    t->ma04 = 1;
    if (t->m510->m4 != 0) return;
    if (t->m508 <= 0) {
        AnimElem& e = (*t->m410)[0];
        bool end;
        if (e.m1c) return;
        if (e.m10 >= 0.0f) end = e.m8 == e.m14;
        else end = e.m8 <= 0.0f;
        if (!end) return;
        func_001A094C(t, 1);
        func_0065A330(t->m9d0, 6);
    } else {
        func_0065A330(t->m9d0, 4);
    }
}
