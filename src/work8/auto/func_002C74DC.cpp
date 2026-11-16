typedef unsigned int u32;
typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern "C" void func_006632F0(void* p, s32 n);

extern "C" void func_002C74DC(char* self) {
    char* b = self + 0x400;
    if (*(u8*)(b + 0x6a) != 0) {
        func_006632F0(self + 0x40c, 2);
    } else {
        s16 h = *(s16*)(b + 0x60);
        if (h > 0) {
            *(s16*)(b + 0x60) = (s16)(h - 1);
        } else {
            func_006632F0(self + 0x40c, 3);
        }
    }
}
