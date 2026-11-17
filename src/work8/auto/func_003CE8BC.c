typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

extern u8 data_00714928[8];
extern s32 func_003D127C(void);
extern void func_003D1240(void);
extern s32 func_00102794(void);
extern void func_0010140C(void);
extern u8 func_001023F8(void);
extern void func_001024E0(void);

s32 func_003CE8BC(void) {
    s32 r = 0;
    if (!data_00714928[0]) {
        r = func_003D127C();
        u32 t1 = (u32)r >> 31;
        if (t1) {
            return r;
        }
        func_003D1240();
        s32 v = func_00102794();
        u32 t = (u32)v & 0x80000000u;
        r = v;
        if ((s32)t < 0) {
            return r;
        }
        data_00714928[1] = 1;
        func_0010140C();
        data_00714928[4] = func_001023F8();
        func_001024E0();
        data_00714928[0] = 1;
    }
    return r;
}
