extern "C" void func_00352210(void*, int, float);
extern "C" void func_00450F34(void*);
struct Base;
struct Entry { void (Base::*pmf)(); };
struct Cls {
    char pad[0x74];
    unsigned int m74;
    signed char m78;
    char pad2[0x84 - 0x79];
    unsigned int m84;
    Base* m88;
    unsigned int m8c;
    Entry* m90;
    void a();
};
void Cls::a() {
    (m88->*(m90[m78].pmf))();
    unsigned int c = m74 + 1;
    m74 = c;
    void* s = this;
    if (m84 != 0) func_00352210((void*)m84, 1, (float)c);
    func_00450F34(s);
}
