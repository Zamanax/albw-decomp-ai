typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;
extern void* func_002C11E8(void*, u32, u32, u32);
extern void func_0016898C(void*, void*);
extern void func_003249B4(void*);
extern void func_00151148(void*, u32);

void func_0028AE5C(u8* self)
{
    u8 req[0x60];
    void* r = func_002C11E8(req, 0, 0, 0);
    func_0016898C(*(void**)(self + 0x580), r);
    func_003249B4(self);
    func_00151148(*(void**)(self + 0x57c), 0);
    f32 k = 0.95f;
    f32* p = (f32*)(self + 0x400);
    *(f32*)(*(u8**)(self + 0x478) + 0x134) = 0.0f;
    p[0x1b0 / 4] = k;
    p[0x1ac / 4] = k;
    p[0x1a8 / 4] = k;
    u32* d = *(u32**)(self + 0x478);
    d[0x164 / 4] |= 0x40000000;
    d[0x74 / 4] = *(u32*)(self + 0x5a8);
    d[0x78 / 4] = *(u32*)(self + 0x5ac);
    d[0x7c / 4] = *(u32*)(self + 0x5b0);
}
