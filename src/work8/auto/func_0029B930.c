extern void func_001E3134(void* self);
extern void* data_0070FB60;
extern void func_001DBE44(void* obj, float* v, int zero);
extern void func_0029BD88(void* a, void* b);
extern void* data_0070B728;
extern void func_004CDA94(void* a, void* b);
extern void func_0029B9CC(void* self);

void func_0029B930(void* self) {
    float v[3];
    func_001E3134(self);
    v[0] = 1000.0f;
    v[1] = 1000.0f;
    v[2] = 1000.0f;
    func_001DBE44(data_0070FB60, v, 0);
    func_0029BD88(*(void**)((unsigned char*)self + 0x138), (unsigned char*)self + 0xe0);
    func_004CDA94(data_0070B728, (unsigned char*)self + 0xfc);
    func_0029B9CC(self);
}
