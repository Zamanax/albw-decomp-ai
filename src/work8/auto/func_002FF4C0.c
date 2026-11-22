typedef unsigned int u32;
typedef int s32;
extern void func_0010E3C4(void*, const void*, u32);
extern void func_001164C4(void*, u32, s32);
extern void func_001164F4(void*, u32);
extern void func_003CB5F0(void*, u32, s32);

void func_002FF4C0(char* self, u32 a1)
{
    s32 h = *(s32*)(self + 0x188);
    if (h << 2 < 0) return;
    func_0010E3C4(self + 0x4c, self + 0x88, 0x10);
    u32 f = *(u32*)(self + 0x188);
    if (a1 != 0) {
        if ((f & 0x10000000) != 0) {
            if ((s32)(f << 4) < 0) return;
            func_001164C4(*(void**)(self + 0x60), (u32)(*(s32*)(self + 0x68) * *(s32*)(self + 0x6c)) << 1, 0xff);
            return;
        }
        if ((s32)(f << 4) >= 0)
            func_001164C4(*(void**)(self + 0x60), (u32)(*(s32*)(self + 0x68) * *(s32*)(self + 0x6c)) << 1, 0xff);
        func_001164F4(*(void**)(self + 0x3c), *(u32*)(self + 0x84));
        return;
    }
    if ((f & 0x10000000) != 0) {
        if ((f & 0x8000000) == 0) {
            func_003CB5F0(self + 0x3c, 1, 0);
            return;
        }
        func_003CB5F0(self + 0x3c, 3, 0);
        return;
    }
    if ((f & 0x8000000) == 0) return;
    *(float*)(self + 0x70) = 1.0f;
    func_003CB5F0(self + 0x3c, 2, 0);
}
