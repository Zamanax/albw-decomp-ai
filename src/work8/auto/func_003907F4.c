typedef unsigned int u32;
typedef int s32;
typedef float f32;

extern char* data_00708998;
extern char data_00712780[];
extern void func_001E8268(void*, void*, void*, void*);

void func_003907F4(char* self) {
    s32 n = *(s32*)(self + 0x4b4) + 1;
    *(s32*)(self + 0x4b4) = n;
    s32 v = *(s32*)(data_00712780 + 0x10);
    if (n < 0xb4) {
        s32 t = n * (n + 1) / 2;
        f32 a = (f32)v;
        f32 b = (f32)t * 6.1387355e-5f;
        v = (s32)(a * b);
    }
    *(s32*)(self + 0x464) += v;
    char* g = data_00708998;
    func_001E8268(*(void**)(g + 0x18), self + 0x414, self + 0x444, self + 0x45c);
}
