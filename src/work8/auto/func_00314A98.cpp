typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" u32 func_00111A64(void*);
extern "C" void* data_007124F0;
inline u32 below(void* r, u32 n) { return (u32)(((unsigned long long)func_00111A64(r) * n) >> 32); }

struct Obj {
    u8 pad0[0x3e8];
    u32 m3e8;
    u8 pad1[0x990 - 0x3ec];
    u32 m990;
    u16 m994;
};

void func_00314A98(Obj* p) {
    if (p->m994 != 0) {
        p->m994 = p->m994 - 1;
    } else {
        u32 a = below((u8*)data_007124F0 + 0x660, 0xb60b60) + 0xb60b60;
        p->m990 = a;
        p->m994 = below((u8*)data_007124F0 + 0x660, 200) + 200;
    }
    u32& acc = p->m3e8;
    acc += p->m990;
}
