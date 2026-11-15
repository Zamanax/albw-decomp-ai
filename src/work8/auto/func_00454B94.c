extern void func_001B6C04(void*);
extern void func_002317C0(void*, float);
extern void func_00231524(void*);
extern void func_002313DC(void*);
extern int func_0055696C(void*, unsigned int);
extern void func_002316CC(void*, float);
extern void* data_0070FB60;

void func_00454B94(char* self) {
    func_001B6C04(self);
    func_002317C0(self + 0x74, 1.0f);
    unsigned char b = *(unsigned char*)(self + 0xd8);
    *(unsigned char*)(self + 0xd9) = 0;
    *(unsigned short*)(self + 0xa0) = 0;
    if (b)
        func_00231524(self + 0xa0);
    else
        func_002313DC(self + 0xa0);
    void* g = data_0070FB60;
    if (!g)
        return;
    int lvl = func_0055696C(g, 0x1f);
    float v = lvl == 3 ? 1.0f : (lvl == 4 ? 2.0f : 0.0f);
    func_002316CC(self + 0xac, v);
}
