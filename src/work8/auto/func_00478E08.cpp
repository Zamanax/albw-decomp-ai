// 0x478E08
extern "C" void func_0066E7A0(void*, int);
struct Sub { char pad[0x3c]; signed char m3C; };
struct Cls {
    char pad1[0xcc];
    char mCC;
    char pad2[0xd0 - 0xcd];
    unsigned char mD0;
    char pad3[0xf0 - 0xd1];
    char mF0;
    char pad4[0x1f4 - 0xf1];
    Sub* m1F4;
    Sub* m1F8;
    void f(int a);
};
void Cls::f(int a) {
    if (mD0 == 2) {
        func_0066E7A0((char*)this + 0xf0, 0xb);
    } else if ((unsigned)(m1F4->m3C - 1) < 5 || (unsigned)(m1F8->m3C - 1) < 5) {
        func_0066E7A0((char*)this + 0xf0, 0xb);
        func_0066E7A0((char*)this + 0xcc, 2);
    }
    signed char s = (signed char)mD0;
    if (s == 0 || s == 2) {
        func_0066E7A0((char*)this + 0xcc, 3);
        if (a == 1) { func_0066E7A0((char*)this + 0xf0, 0xc); return; }
        func_0066E7A0((char*)this + 0xf0, 0xe);
    }
}
