typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

extern f32 func_0058AA40(void*);
extern void func_0051D39C(void*, u32, s32);
extern u32 func_0058ACC8(void*, f32);
extern void func_0037EC94(void*);
extern u32 func_0058A8F0(void*);
extern void func_006678C0(void*, s32);

void func_0037EE4C(char* self) {
    f32 d = func_0058AA40(self);
    if (!(d >= 15.0f)) {
        func_0051D39C(self + 0x3e8, *(u32*)(self + 0xad8), 0xf);
    }
    if (func_0058ACC8(self, 10.0f)) {
        func_0037EC94(self);
    }
    if (func_0058A8F0(self) != 0) {
        u8 z = 0;
        *(u8*)(self + 0xb33) = z;
        char* q = self + 0xb00;
        u16 h = *(u16*)(q + 0x2a);
        if (h != 0) {
            if (*(u8*)(q + 0x32) == 0) return;
        }
        func_006678C0(self + 0xa48, 6);
    }
}
