extern "C" void func_00421C30(void*);
extern "C" void func_00352210(void*, int, float);
struct Base;
struct Entry { void (Base::*pmf)(); };
struct Cls {
    char pad[0x74];
    unsigned int m74;
    signed char m78;
    char pad2[0x84 - 0x79];
    unsigned int m84;
    Base* m88;
    char pad3[0x90 - 0x8c];
    Entry* m90;
    char pad4[0xa8 - 0x94];
    void* ma8;
    void f();
};
void Cls::f() {
    func_00421C30(ma8);
    (m88->*(m90[m78].pmf))();
    unsigned int c = m74 + 1;
    m74 = c;
    if (m84 != 0) func_00352210((void*)m84, 1, (float)c);
}
