#include "albw_types.h"
typedef unsigned int u32;
typedef float f32;
extern f32 func_00590EC8(f32, f32);
extern void func_00169A80(void*);
extern void func_00168E9C(void*, void*, u32);
extern void func_004CEAF0(void*);

void func_0028765C(char* p)
{
    if (p[0x2d7]) return;
    {
        u32* o = *(u32**)(p + 0x40c);
        f32* a = (f32*)(p + 0x400);
        o[0x164/4] |= 0x40000000;
        o[0x8c/4] = *(u32*)(p + 0x3d0);
        o[0x9c/4] = *(u32*)(p + 0x3d4);
        o[0xac/4] = *(u32*)(p + 0x3d8);
        {
            f32 q = a[0x1c/4];
            s32 n = *(s32*)(p + 0x420);
            f32 r = q / (f32)n;
            f32 num;
            if (r >= 1.0f) {
                num = a[0x18/4];
            } else {
                num = 0.0f;
                if (r <= 0.0f) {
                } else {
                    f32 t = func_00590EC8(r, 0.7f);
                    num = a[0x18/4] * t;
                }
            }
            f32 d = num / a[0x18/4];
            o = *(u32**)(p + 0x40c);
            o[0x164/4] |= 0x40000000;
            *(f32*)((char*)o + 0x74) = d;
            *(f32*)((char*)o + 0x78) = d;
            *(f32*)((char*)o + 0x7c) = d;
        }
    }
    func_00169A80(*(void**)(p + 0x410));
    func_00168E9C(*(void**)(p + 0x410), *(void**)(p + 0x40c), 0);
    func_004CEAF0(*(void**)(p + 0x40c));
}
