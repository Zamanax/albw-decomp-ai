typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern void* func_0010DA7C(void*, void*, u32);
extern u32 ro_006ED880;

void* func_004EDC9C(void* self) {
    void * t3 = func_0010DA7C(self, 0, 3);
    char* p = (char*)t3;
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x0) = ((int)&ro_006ED880);
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x18) = 0;
    *(u32*)(p + 0x1c) = 1;
    *(u32*)(p + 0x20) = 0;
    *(u16*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
    *(u16*)(p + 0x2c) = 0xff;
    u32* q = (u32*)(p + 0x30);
    q[0] = 0;
    q[2] = (u32)p;
    q[1] = 0;
    q[3] = 0;
    *(u32*)(p + 0x40) = 0;
    *(u8*)(p + 0x44) = 1;
    return p;
}
