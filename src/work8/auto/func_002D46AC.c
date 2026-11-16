typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

struct Obj {
    char pad0[0x24];
    void* m24;
    char pad1[4];
    u32 m2c;
    u32 m30;
    float m34;
};

void func_00663BDC(void* self, s32 v);
void func_004CF5B0(void* p, s32 a, s32 b, s32 c);

void func_002D46AC(struct Obj* p) {
    if (p->m2c < p->m30) {
        p->m2c++;
    } else {
        func_00663BDC(p, 2);
    }
    float f;
    if (p->m30 == 0 || p->m2c == 0) {
        f = 0.0f;
    } else if (p->m30 <= p->m2c) {
        f = 1.0f;
    } else {
        f = (float)p->m2c * p->m34;
    }
    f = f * 255.0f;
    s32 n = (s32)f;
    if ((float)n != f && 0.0f <= f) {
        n++;
    }
    func_004CF5B0(p->m24, 0, 0, (u8)n);
}
