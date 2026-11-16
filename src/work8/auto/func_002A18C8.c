extern void* data_0070FB60;
int func_00556E64(void* e);
void func_00661FE4(void* p, int v);

void func_002A18C8(char* self) {
    unsigned int* d = (unsigned int*)(self + 0x3d0);
    unsigned int* s = (unsigned int*)self;
    d[0] = s[2];
    d[1] = s[3];
    d[2] = s[4];
    void* p = data_0070FB60;
    if (p == 0) return;
    if (func_00556E64(p) != 0) return;
    unsigned int a = *(unsigned int*)(self + 0x910);
    unsigned int b = *(unsigned int*)(self + 0x914);
    if (a < b) {
        *(unsigned int*)(self + 0x910) = a + 1;
        return;
    }
    func_00661FE4(self + 0x938, 1);
}
