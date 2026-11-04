typedef unsigned int u32;
extern char data_0070D7D0[];
extern char data_00714270[];
extern "C" unsigned func_005826A4(unsigned, unsigned, unsigned, unsigned);
extern "C" void func_0044121C(unsigned, unsigned);
struct G7_006F5980_lv_vp {
    virtual void G7_vf();
    unsigned f4;
    G7_006F5980_lv_vp(unsigned a0) { f4 = a0; }
};
struct Obj2DF94C {
    char _pad[0x14];
    unsigned m14;
};
void func_002DF94C(Obj2DF94C* self) {
    unsigned lv[4];
    lv[0] = 0;
    lv[1] = 0;
    lv[2] = 0;
    lv[3] = (unsigned)-1;
    G7_006F5980_lv_vp name((unsigned)"Common");
    unsigned k = (unsigned)data_00714270;
    if (func_005826A4(*(unsigned*)data_0070D7D0, (unsigned)lv, (unsigned)&name, k))
        func_0044121C(self->m14, (unsigned)lv);
}
