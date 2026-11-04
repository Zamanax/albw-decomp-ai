extern "C" void* data_0070FB60;
extern "C" unsigned func_005568B0(void*);
extern "C" unsigned func_0053F090(void*);
extern "C" void func_0010C7F8(void*, int, float);
extern "C" void func_0010BC94(void*, int);

struct S2963D0 {
    char pad0[0xc4];
    char mC4[0x178 - 0xc4];
    unsigned count;
    unsigned cap;
    void** data;
};

void func_002963D0(S2963D0* self) {
    if (func_005568B0(data_0070FB60) != 0) return;
    if (func_0053F090(data_0070FB60) == 0) return;
    func_0010C7F8(self->count > 1 ? self->data[1] : 0, 15, 0.0f);
    func_0010BC94(self->mC4, 2);
}
