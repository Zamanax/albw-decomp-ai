typedef float f32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct In { char pad[4]; f32 f4; } In;
typedef struct Mgr { char pad[0x1c]; In* in; } Mgr;

extern Mgr* data_0070FB60;
extern void func_0065A5B8(void*, s32);
void func_001A4AE4(u8* a0) {
    u8* p = a0 + 0x8bc;
    if (*(s32*)p >= 0x14) {
        func_0065A5B8(p, 3);
        return;
    }
    if (*(u8*)(a0 + 0x8fe) == 0) return;
    s32 lim = 0x41200000;
    f32 d = *(f32*)(a0 + 0x3d4);
    f32 y = data_0070FB60->in->f4;
    f32 e = y - d;
    if (*(s32*)&e > lim) {
        func_0065A5B8(p, 0);
        return;
    }
    if (*(u32*)&e <= 0xC1200000u) return;
    func_0065A5B8(p, 0);
}
