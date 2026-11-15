extern void func_0014FD6C(void*, float*, int);
extern void func_00661FE4(void*, int);

void func_002A1754(char* self) {
    unsigned short mode = *(unsigned short*)(self + 0x2c);
    if (mode != 1) {
        float v[3];
        v[0] = 0.0f;
        v[1] = 0.5f;
        v[2] = 0.0f;
        func_0014FD6C(self, v, *(int*)(self + 0x3e8));
        func_00661FE4(self + 0x938, 0);
    } else {
        unsigned int* flags = (unsigned int*)(self + 0x59c);
        *flags = *flags | 0x1000;
    }
}
