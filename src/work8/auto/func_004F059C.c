typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
extern char* data_007124F0;
extern u32 func_00111A64(char*);
extern u32 ro_0069355C;

static inline u32 rnd(char* p, u32 m){ return (u32)(((u64)func_00111A64(p) * m) >> 32); }
s32 func_004F059C(u32 self) {
    u32 r = rnd(data_007124F0 + 0x660, 100);
    if (self == ro_0069355C) {
        if (r < 10) return 0;
        if (r < 15) return 7;
        if (r < 23) return 9;
        return -1;
    }
    if (r < 20) return 0;
    if (r < 30) return 7;
    return -1;
}
