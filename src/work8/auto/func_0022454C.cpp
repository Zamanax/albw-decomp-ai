typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef float f32;

struct Vec3 { f32 x, y, z; };

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

extern "C" void func_0036BE78(void*);
extern "C" void func_0036C058(void*, u32, u32, u8);
extern "C" void func_0065E774(void*, u32);
extern "C" void func_00115C54(Vec3*, const Vec3*, const Vec3*);

struct This2244 {
    u8 pad00[0x3d0];
    Vec3 m3d0;               // 0x3d0
    Vec3 m3dc;               // 0x3dc
    u8 pad0[0x468 - 0x3e8];
    s32 m468;                // 0x468
    u8 pad1[0x4b4 - 0x46c];
    void* m4b4;              // 0x4b4
    u8 pad2[0x580 - 0x4b8];
    u8 m580;                 // 0x580
    u8 pad3[0x685 - 0x581];
    u8 m685;                 // 0x685
    u8 pad4[0x68c - 0x686];
    AnimArr* m68c;           // 0x68c
    u8 pad5[0x710 - 0x690];
    Vec3 m710;               // 0x710
};

void func_0022454C(This2244* t) {
    if (t->m468 == 10) {
        t->m580 = 2;
        t->m4b4 = (char*)t + 0x704;
        func_0036C058((char*)t + 0x48c, 0xffffffffu, 0xffffffffu, 0);
    }
    if (t->m468 >= 10) func_0036BE78((char*)t + 0x48c);
    AnimElem& e = (*t->m68c)[0];
    if (!e.m1c && e.isEnd()) {
        func_0065E774((char*)t + 0x468, 0xb);
        u32* d = (u32*)&t->m3d0;
        u32* s = (u32*)&t->m710;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        t->m685 = 0;
    } else {
        Vec3* p = &t->m3d0;
        func_00115C54(p, p, &t->m3dc);
        t->m3dc.y -= 0.06f;
    }
}
