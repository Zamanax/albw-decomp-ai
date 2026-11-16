typedef unsigned int u32;
typedef unsigned char u8;

extern void func_003E54A8(void* p, u32 a, u32 b, u32 c);

typedef struct Desc {
    char p0[4];
    u8 f4;
    char p5[3];
    u32 f8;
    u32 fc;
    char p10[4];
    u32 f14;
} Desc;

void func_003E5414(char* self, u32 a1, Desc* a2) {
    if (a1 == 0 || a2 == 0) return;
    if (a2->f4 == 0) {
        func_003E54A8(self + a2->f14, a1, 1, 0);
        func_003E54A8(self + a2->f8, a1, 0, 0);
    } else {
        func_003E54A8(self + a2->f14, a1, 1, 0);
        func_003E54A8(self + a2->f8, a1, 0, 0);
        func_003E54A8(self + a2->fc, a1, 0, 1);
    }
}
