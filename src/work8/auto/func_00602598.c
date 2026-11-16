typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef void* (*AllocFn)(u32, u32, u32, u32);
extern AllocFn data_00714820;
extern void func_00110490(void*, u32);

void* func_00602598(void* self) {
    AllocFn f = data_00714820;
    void* p;
    if (f == 0) {
        p = 0;
    } else {
        p = f(0x10000, 0x100, 0, 0x78);
        if (p != 0) {
            func_00110490(p, 0x78);
            *(u32*)((char*)p + 0x04) = 0x2600;
            *(u32*)((char*)p + 0x00) = 0x2600;
            *(u32*)((char*)p + 0x08) = 0x2901;
            *(u32*)((char*)p + 0x0c) = 0x2901;
            *(f32*)((char*)p + 0x24) = 0.0f;
            *(f32*)((char*)p + 0x28) = 0.0f;
            *(s32*)((char*)p + 0x2c) = 0;
            *(s32*)((char*)p + 0x14) = -1000;
            *(f32*)((char*)p + 0x20) = 0.0f;
            *(f32*)((char*)p + 0x1c) = 0.0f;
            *(f32*)((char*)p + 0x18) = 0.0f;
            *(void**)((char*)p + 0x74) = self;
        }
    }
    return p;
}
