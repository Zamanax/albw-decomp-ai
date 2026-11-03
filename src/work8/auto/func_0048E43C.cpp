typedef unsigned char u8;
struct M20 { virtual void a(); virtual void destroy(); };
struct Instance { u8 pad[0x20]; M20* m20; void* m24; };
struct G { Instance* m0; void* m4; };
extern "C" G data_00714F90;
extern "C" char ro_006F55B8[];
extern "C" char ro_006A8A90[];
extern "C" void func_00102130(const char* s);
extern "C" void func_0058FA08(void* p);
extern "C" void func_004A1520(void* self);
struct S { void* vt; void dtor(); };
void S::dtor() {
    void* vt = ro_006F55B8;
    *(void**)this = vt;
    void* m = data_00714F90.m4;
    if (this == m) {
        data_00714F90.m4 = 0;
        Instance* p = data_00714F90.m0;
        if (p->m20) {
            p->m20->destroy();
            p->m20 = 0;
        }
        func_00102130(ro_006A8A90);
        func_0058FA08(p->m24);
        data_00714F90.m0 = 0;
    }
    func_004A1520(this);
}
