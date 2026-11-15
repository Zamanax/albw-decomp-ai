typedef unsigned int u32;
typedef unsigned short u16;
extern void func_002317C0(void* control, float value);
extern void func_006653E8(void* p, unsigned int v);
void func_0031C0B8(char* p) {
    if (*(float*)(p + 0xe0) >= 0.0f) {
        char* q = p + 0x1c;
        u16 a = 9;
        u16 b = 2;
        u32 v = *(u32*)q;
        char* c = q + 0xac;
        *(u32*)(c + 8) = v;
        *(u16*)(c + 2) = a;
        *(u16*)(c) = b;
        func_002317C0(c, 1.0f);
        func_006653E8(p + 0x50, 0);
    }
}
