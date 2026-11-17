extern "C" void func_0010E0E0(void*);
extern "C" void func_0010E15C(void*);
extern "C" void func_005FF9AC(int, void*);
extern "C" void* func_001E6CE8(void*);
extern "C" void func_004A1520(void*);
extern char ro_006DE848[];
extern void* data_00715160;
struct Cls {
    void* vt;
    char pad1[0x28 - 4];
    void* m28[2];
    char pad2[0x45 - 0x30];
    unsigned char m45;
};
extern "C" void func_002FEAFC(Cls* p) {
    p->vt = ro_006DE848;
    if (p->m45 != 0) {
        func_0010E0E0(data_00715160);
        p->m45 = 0;
        for (int i = 0; i < 2; i++) {
            void* t = p->m28[i];
            func_005FF9AC(1, &t);
        }
        func_0010E15C(data_00715160);
    }
    func_004A1520((char*)func_001E6CE8((char*)p + 0x10) - 0x10);
}
