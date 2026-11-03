typedef unsigned char u8;
struct G { void* m0; void* m4; };
struct M34 { virtual void a(); virtual void destroy(); };
struct Instance { u8 pad[0x34]; M34* m34; };
struct S { void* vt; virtual void dtor(); };
extern "C" void func_004A1520(void*);
extern "C" G data_007153D0;
extern "C" char ro_006F5080[];
void S::dtor() {
    void* vt = ro_006F5080;
    *(void**)this = vt;
    void* m = data_007153D0.m4;
    if (this == m) {
        data_007153D0.m4 = 0;
        Instance* p = (Instance*)data_007153D0.m0;
        if (p->m34) { p->m34->destroy(); p->m34 = 0; }
        data_007153D0.m0 = 0;
    }
    func_004A1520(this);
}
