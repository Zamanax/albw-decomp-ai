typedef unsigned int u32;
typedef unsigned char u8;

void* func_0048F99C(void* p, u32 a, u32 b, u32 c, u32 d);
extern char ro_006F43E4[];

void func_00489C30(void* self, u32 p1) {
    char* o = (char*)func_0048F99C((char*)self + 4, 0x1c, 0x14, 0x18, 0xf) - 4;
    *(void**)o = ro_006F43E4;
    *(u8*)(o + 0x134) = 0;
    *(u32*)(o + 0x138) = p1;
    *(u32*)(o + 0x140) = (u32)(o + 0x13c);
    *(u32*)(o + 0x144) = 0;
    *(u32*)(o + 0x13c) = (u32)(o + 0x13c);
    *(u32*)(o + 0x150) = (u32)(o + 0x14c);
    *(u32*)(o + 0x154) = 0;
    *(u32*)(o + 0x14c) = (u32)(o + 0x14c);
    *(u32*)(o + 0x148) = 4;
    *(u32*)(o + 0x158) = 0x148;
}
