typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Inner { char pad[4]; f32 f4; };
struct Mgr { char pad[0x1c]; Inner* in; };
extern Mgr* data_0070FB60;
extern void func_0065A5B8(void*, s32);
void func_001A4A88(char* p) {
    f32 x = *(f32*)(p + 0x3d4);
    f32 y = data_0070FB60->in->f4;
    f32 d = y - x;
    if ((s32)*(u32*)&d > 0x41200000) return;
    if (*(u32*)&d > 0xc1200000u) return;
    func_0065A5B8(p + 0x8bc, 1);
}
