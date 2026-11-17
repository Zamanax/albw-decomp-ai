typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef unsigned char u8;

extern void* data_0070D858;
extern s32 func_005238E4(void* m, s32 v);

s32 func_0054EB88(u8* self, s32* out) {
    u32 a = self[0x475];
    u8* p = self + 0x400;
    if (a != 0) {
        return 0;
    }
    if (p[0x76] == 1) {
        *out = func_005238E4(data_0070D858, *(s16*)(self + 0x2c));
    } else {
        *out = *(s16*)(self + 0x2c);
    }
    return 1;
}
