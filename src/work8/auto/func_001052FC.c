typedef unsigned int u32;
extern unsigned char data_00714838[];
extern u32 func_001088D4(void);
extern u32 func_0010893C(void);
extern void func_0010873C(u32, u32, u32);
inline void diagnose(u32 r, u32 pc) { u32 s = r >> 31; if (s) func_0010873C(r, pc, s); }

void func_001052FC(u32 a) {
    if (a) {
        data_00714838[3] = 1;
        diagnose(func_001088D4(), __current_pc());
        return;
    }
    if (data_00714838[3] == 0) return;
    data_00714838[3] = 0;
    u32 r = func_0010893C();
    if (r == 0xd8a02a05 || r == 0xd9001bf7) return;
    diagnose(r, __current_pc());
}
