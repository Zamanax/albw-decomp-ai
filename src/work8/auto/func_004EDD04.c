typedef unsigned int u32;
typedef unsigned char u8;

extern void func_0010F1F8(void*);
extern void* func_004A1520(void*);

void* func_004EDD04(void* self) {
    *(u32*)self = 0x006ED880;
    u8* owner = *(u8**)((u8*)self + 0x3c);
    u8* node = 0x30 + (u8*)self;
    if (owner) {
        *(u8**)(0xc + node) = 0;
        u32* cnt = (u32*)(owner + 8);
        func_0010F1F8(node);
        *cnt = *cnt - 1;
    }
    return func_004A1520(self);
}
