typedef float f32;
typedef int s32;
extern void func_00663434(void* p, s32 n);

void func_002C82F4(char* p)
{
    f32 v = *(f32*)(p + 0x488) + 0.05f;
    *(f32*)(p + 0x488) = v;
    if (*(s32*)&v < 0x3f800000) return;
    *(f32*)(p + 0x488) = 1.0f;
    func_00663434(p + 0x40c, 3);
}
