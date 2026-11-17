extern void func_0066CC58(void*, int);
extern void func_00446EAC(void*);
extern void func_00447E28(void*, int, unsigned, int);

void func_0044A9F8(char* self) {
    signed char st = *(signed char*)(self + 0x15c);
    if (st != 2 && st != 1) {
        if (st == 6) func_0066CC58(self + 0x158, 7);
        return;
    }
    if (*(unsigned*)(self + 0x234) == 0) func_00446EAC(self);
    {
        int z = 0;
        func_00447E28(self, 1, *(unsigned*)(self + 0x23c), z);
        func_00447E28(self, 0, *(unsigned*)(self + 0x240), z);
    }
    *(unsigned char*)(self + 0x294) = 1;
    func_0066CC58(self + 0x158, 3);
}
