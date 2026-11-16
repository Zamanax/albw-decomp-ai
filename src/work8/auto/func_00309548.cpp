typedef unsigned int u32;
typedef unsigned char u8;

extern u32 ro_006F5988[];

class StrObj_006F5988 {
public:
    const u32* vt;
    const char* p;
    StrObj_006F5988(const char* s) : vt(ro_006F5988) { p = s; }
};

extern "C" void* func_00584C14(void* m, const StrObj_006F5988& name);
extern "C" void func_004CEA18(void* m, u32 on, void* n);
extern "C" void func_004CF478(void* m, u32 on, void* x);

void func_00309548(char* self, u32 arg) {
    void** pm = (void**)(self + 0x40c);
    if (*(u8*)(self + 0x436) != 0) {
        const char* s = "after";
        void* n = func_00584C14(*(void**)(self + 0x40c), StrObj_006F5988(s));
        func_004CEA18(*pm, arg, n);
        n = func_00584C14(*pm, StrObj_006F5988("before"));
        func_004CEA18(*pm, arg ^ 1, n);
        return;
    }
    func_004CF478(*(void**)(self + 0x40c), arg ^ 1, 0);
}
