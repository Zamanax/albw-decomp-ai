typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct Random Random;
typedef struct En En;

extern void func_004FABDC(En* e, s32 a, s32 b, s32 c);
extern Random* func_0058A7D4(En* e);
extern u32 func_00111A64(Random* r);

struct En {
    u8 pad0[0x3dc];
    f32 m3dc;
    f32 m3e0;
    f32 m3e4;
    u8 pad1[0x904 - 0x3e8];
    u32 m904;
    u8 pad2[0x928 - 0x908];
    u32 m928;
    u8 pad3[0x965 - 0x92c];
    u8 m965;
};

void func_001AAC40(En* p) {
    u32 zero = 0;
    func_004FABDC(p, 1, -1, 0);
    p->m904 = zero;
    p->m3dc = 0.0f;
    p->m3e0 = 0.0f;
    p->m3e4 = 0.0f;
    if (func_00111A64(func_0058A7D4(p)) & 1) {
        p->m965 = 1;
    } else {
        p->m965 = (u8)zero;
    }
    u32 flag = p->m965;
    if (flag != 0) {
        p->m928 = p->m928 + 0x40000000;
    } else {
        p->m928 = p->m928 + 0xc0000000;
    }
}
