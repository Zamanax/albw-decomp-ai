static inline void clr59c(char* p, unsigned int m) {
    unsigned int x = *(unsigned int*)(p + 0x59c);
    *(unsigned int*)(p + 0x59c) = x & ~m;
}
void func_001B040C(char* self, int a) {
    if (a != 10) {
        *(float*)(self + 0x3dc) = 0.0f;
        *(float*)(self + 0x3e4) = 0.0f;
        clr59c(self, 8u);
    }
    *(unsigned char*)(self + 0x909) = 1;
    char* base = self + 0x800;
    unsigned int v = **(unsigned int**)(self + 0x9b8);
    *(unsigned int*)(base + 0xe4) = v;
}
