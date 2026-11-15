typedef unsigned int u32;
extern void* func_00100118(void*, void (*)(void*), u32, u32);
extern void func_003E6760(void*);
void func_0041E750(char* p) {
    char* o = (char*)func_00100118(p, func_003E6760, 4, 2);
    *(float*)(o + 0x1c) = 0.0f;
    *(float*)(o + 0x20) = 0.0f;
    *(u32*)(o + 0x24) = 0;
    *(u32*)(o + 0x28) = 0;
    *(unsigned char*)(o + 0x2c) = 0;
    *(unsigned char*)(o + 0x2d) = 0;
    *(unsigned char*)(o + 0x2e) = 0;
    *(u32*)(o + 0) = 0xffffffffu;
    *(u32*)(o + 4) = 0xffffffffu;
    *(float*)(o + 8) = 1.0f;
    *(float*)(o + 0xc) = 1.0f;
    *(float*)(o + 0x10) = 0.0f;
    *(float*)(o + 0x14) = 0.0f;
    *(float*)(o + 0x18) = 0.0f;
}
