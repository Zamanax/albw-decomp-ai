extern char data_0070D7D0[];
extern char ro_0069E91C[];
extern "C" unsigned func_005826A4(unsigned, unsigned, unsigned, unsigned);
extern "C" unsigned func_00178AE8(void*, void*, unsigned, unsigned);
struct G7_006F5988_lv_vp {
    virtual void G7_vf();
    unsigned f4;
    G7_006F5988_lv_vp(unsigned a0) { f4 = a0; }
};
extern "C" unsigned func_00178CD8(void* p, void* output, unsigned input) {
    unsigned lv[4];
    lv[0] = 0;
    lv[1] = 0;
    lv[2] = 0;
    lv[3] = (unsigned)-1;
    G7_006F5988_lv_vp name((unsigned)ro_0069E91C);
    if (func_005826A4(*(unsigned*)data_0070D7D0, (unsigned)lv, (unsigned)&name, input))
        return func_00178AE8(p, output, lv[0], lv[2]);
    return (unsigned)output;
}
