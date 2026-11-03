extern "C" void* func_00412BB4(void*);
extern "C" void* func_00412A3C(void*, int);
extern "C" void func_00412C68(void*, void*);
struct Cls {
    void f(float x, void* p);
    template<class T0> void hlp0(T0 r) {
        *(unsigned char*)(r + 4) = 0x2d;
        *(void**)(r + 0x10) = (char*)this + 0x114;
    }
};
void Cls::f(float x, void* p) {
    void* q = func_00412BB4(this);
    void* q_c16 = q;
    char* r = (char*)func_00412A3C(q_c16, 7);
    *(int*)(r + 0xc) = *(int*)((char*)q + 0x184);
    hlp0(r);
    *(void**)(r + 0x14) = p;
    *(float*)(r + 0x18) = x;
    void* q_c84 = q;
    char* r_c1 = r;
    func_00412C68(q_c84, r_c1);
}
