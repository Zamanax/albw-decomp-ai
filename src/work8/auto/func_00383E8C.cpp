typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct P {
    u32 m0;
    char p4[4];
    f32 m8;
    char pc[4];
    f32 m10;
    f32 m14;
    char p18[4];
    u8 m1c;
};

struct Arr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    P* mData;
    P& operator[](s32 i) {
        if ((u32)i < (u32)mNum) return mData[i];
        return mData[0];
    }
};

struct Self {
    char p0[0x1c];
    Arr* m1c;
};

bool func_003840A0(Self* self, u32 x);
void func_003842C0(Self* self, u32 a, u32 b, u32 c);

void func_00383E8C(Self* self) {
    if (!func_003840A0(self, 0x4f)) return;
    P* p = &(*self->m1c)[0];
    if (p->m1c != 0) return;
    if (p->m10 >= 0.0f) {
        if (p->m8 == p->m14) func_003842C0(self, 0x50, 0xa, 1);
    } else {
        if (p->m8 <= 0.0f) func_003842C0(self, 0x50, 0xa, 1);
    }
}
