typedef int s32;
typedef float f32;
extern "C" bool func_0051D2F4(s32*, s32, f32, s32, s32);
extern "C" bool func_0058A8F0(void*);
extern "C" void func_006678C0(void*, s32);
void f381C44(char* self) {
    s32* cur = (s32*)(self + 0x800 + 0x218);
    func_0051D2F4(cur, *(s32*)(self + 0xad8), 0.4f, 0xb60b60, 0x38e38e3);
    if (func_0058A8F0(self)) func_006678C0(self + 0x800 + 0x248, 6);
}
