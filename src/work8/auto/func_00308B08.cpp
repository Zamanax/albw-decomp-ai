extern "C" void func_002E1B70(void*);
extern "C" void* func_005027C4(void*);
extern "C" void func_001510A4(void*);

extern "C" void func_00308B08(char* self) {
    unsigned vt = 0x006df190;
    char* s = self + 0x400;
    *(unsigned*)(self + 0x320) = vt + 0x54;
    unsigned vt2 = 0x006c88bc;
    *(unsigned*)self = vt;
    *(unsigned*)(self + 0x458) = vt2;
    char* m = s + 0x104;
    func_002E1B70(m);
    char* r = (char*)func_005027C4(m - 0xac);
    func_001510A4(r - 0x400 - 0x58);
}
