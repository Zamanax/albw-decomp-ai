extern float func_004F898C(void);
extern void func_004F8964(float* vy, int clamp, float g);
extern void func_001A786C(int self, int a);
extern int func_0058A8F0(int self);
extern void func_0065A840(int p, int b);

void func_001A701C(int p) {
    float g = func_004F898C();
    func_004F8964((float*)(p + 0x3e0), 1, g);
    func_001A786C(p, 1);
    if (*(float*)(p + 0x800 + 0x128) == 0.0f) {
        char* q = *(char**)(p + 0x8e4);
        q[0x61] = 0;
    }
    if (func_0058A8F0(p)) {
        func_0065A840(p + 0x800 + 0xbc, 0);
    }
}
