typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern void func_0045F178(void*, u32);
extern void func_0043D280(void*, u32);

static u32 pickId(u32 mode) {
    if (mode == 0) return 0xd;
    if (mode == 1) return 0xe;
    if (mode == 2) return 0xf;
    return 0xe;
}
void func_0051BB74(char* self, u32 a, u32 flag, u32 mode) {
    u32 id = pickId(mode);
    void** objp = (void**)(self + 0x14);
    void** vt = (void**)*objp;
    void* (*fp)(void*, u32) = (void*(*)(void*, u32))vt[2];
    u8* r = (u8*)fp(objp, id);
    if (r) {
        r[0xe] = 1;
    }
    func_0045F178(r, a);

    if (flag) {
        void* p = *(void**)(self + 0x80);
        u32 one = 1;
        if (p) {
            func_0043D280(p, one);
        }
    } else {
        u16* h = (u16*)(self + 0x33e);
        *h |= 0x10;
    }
}
