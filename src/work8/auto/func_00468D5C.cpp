extern "C" void func_0012C85C(void*);
extern "C" int func_0051E300(void*);

struct T {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct Arr {
    unsigned int num;
    unsigned int cap;
    void** data;
};

inline void* arr_at(Arr* a, unsigned int i) { return i < a->num ? a->data[i] : 0; }

struct ClsB {
    char pad[0x148];
    Arr mArr;
    void b();
};

void ClsB::b() {
    func_0012C85C(this);
    for (int i = 0; i < 0x21; i++) {
        Arr* a = &mArr;
        T* p = (T*)arr_at(a, (unsigned int)i);
        if (func_0051E300(p)) {
            p->v3();
        }
    }
}
