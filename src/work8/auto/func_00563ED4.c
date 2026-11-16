typedef unsigned int u32;
typedef u32 (*VFn00563ED4)(void*, void*, u32, u32*, u32, u32, u32);
extern void func_00110490(void*, u32);

u32 func_00563ED4(void* self, void* buf, u32 p2) {
    if (p2 == 0) {
        return 0xe0e10bfd;
    }
    u32 tmp = 0;
    func_00110490(buf, 0x60);
    u32 r = (*(VFn00563ED4*)((char*)*(void**)self + 0x34))(self, buf, 0x60, &tmp, p2, 2, 0x12);
    if ((r << 22) != 0xfdc00000u) {
        if (tmp == 0) {
            r = 0xc8810bef;
        }
    }
    return r;
}
