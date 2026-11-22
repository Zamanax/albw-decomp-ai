typedef unsigned int u32; typedef int s32; typedef unsigned char u8; typedef signed char s8; typedef float f32;
extern void* data_0070D858;
extern f32 func_00523958(void*);
extern void func_0023194C(void*, s32);
extern f32 func_00532B54(void*);
extern void func_002317C0(void*, f32);
extern void func_0012C718(void*);
void func_004801E0(char* p) {
    void* g = data_0070D858;
    if (*(u8*)((char*)g + 0x70) == 4) {
        f32 v = func_00523958(g);
        f32 m = *(f32*)(p + 0xd0) * v;
        func_0023194C(p + 0xa8, (s32)m);
        if (v >= 0.75f) {
            if (func_00532B54(p + 0x9c) < 1.0f) {
                func_002317C0(p + 0x9c, 1.0f);
            }
        }
        return;
    }
    s8 kd = *(s8*)(p + 0xd);
    if (kd == 1) { func_0012C718(p); return; }
    if (kd == 3 && *(u8*)(p + 0xe) == 3) { func_0012C718(p); }
}
