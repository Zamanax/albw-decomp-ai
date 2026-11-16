typedef unsigned int u32;
typedef int s32;
extern void* data_00708998;

int func_004DD20C(void* self, const float* a, int f) {
    char* o = *(char**)((char*)data_00708998 + 0x18);
    if (o == 0) return (int)o;
    const float* b = (const float*)(o + 0x1b0);
    float dx = a[0] - b[0];
    float dy = a[2] - b[2];
    if (f) {
        if (*(u32*)&dx > 0xc1200000u) return 1;
        if (*(s32*)&dx > (s32)0x41200000) return 1;
        if (*(u32*)&dy > 0xc1200000u) return 1;
        if (*(s32*)&dy > (s32)0x41200000) return 1;
        return 0;
    }
    if (*(u32*)&dx > 0xc1300000u) return 1;
    if (*(s32*)&dx > (s32)0x41300000) return 1;
    if (*(u32*)&dy > 0xc1300000u) return 1;
    if (*(s32*)&dy > (s32)0x41300000) return 1;
    return 0;
}
