extern int func_0051D27C(void* p, int target, unsigned int step);
extern void func_0065AAC8(void* p, int v);
extern unsigned int data_0070AE14;

void func_001AA810(char* self) {
    unsigned int step = data_0070AE14;
    int target = *(int*)(self + 0x928);
    if (func_0051D27C(self + 0x3e8, target, step) != 0) {
        if (*(unsigned char*)(self + 0x965) != 0)
            *(unsigned int*)(self + 0x928) = *(unsigned int*)(self + 0x928) + 0x40000000;
        else
            *(unsigned int*)(self + 0x928) = *(unsigned int*)(self + 0x928) + 0xc0000000;
        func_0065AAC8(self + 0x904, 5);
    }
}
