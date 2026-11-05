typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;


#include "sead_string.h"
namespace sead {

}

struct AnimElem {
    u32 m0, m4;
    f32 m8;
    u32 mC;
    f32 m10;
    f32 m14;
    u32 m18;
    u8 m1c;
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
    AnimElem& operator[](s32 i) {
        if ((u32)i < (u32)mNum) return mData[i];
        return mData[0];
    }
};

struct Self {
    char p0[0x1c];
    AnimArr* m1c;
};

struct Game {
    char p0[0x8c0];
    Self mS;
};

struct Cls {
    void** vt;
    char p4[0x48 - 4];
    Game* m48;
};

extern "C" bool func_00542D5C(Game* g);
extern "C" bool func_003840A0(Self* s, u32 n);
extern "C" void func_004EA17C(void* snd, const sead::SafeString& name, const void* pos);
extern "C" void func_003B1740(Cls* self);
extern void* data_00711F50;

extern "C" void func_003BA694(Cls* self) {
    if (func_00542D5C(self->m48)) {
        AnimElem& e = (*self->m48->mS.m1c)[0];
        if (!e.m1c) {
            if (e.isEnd()) ((void (*)(Cls*))self->vt[63])(self);
        }
    }
    if (func_003840A0(&self->m48->mS, 0xf)) {
        func_004EA17C(data_00711F50, sead::SafeString("SE_PL_SLIDE"), 0);
    }
    func_003B1740(self);
}
