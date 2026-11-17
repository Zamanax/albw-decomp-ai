typedef unsigned char u8;
typedef unsigned int u32;
extern void func_001B6C2C(void* p);
extern void func_001B6A48(void* p);

void func_0051B7D8(u8* self, u32 flag) {
    u8* child = *(u8**)(self + 0xd4);
    if (child == 0) return;
    if ((child[0xd] != 0 || child[0xe] != 0) && child[0x94] != 0) {
        u32 b = flag ^ 1;
        if (b == 0) *(u32*)(child + 0x18) &= ~4u;
        else *(u32*)(child + 0x18) |= 4u;
        child = *(u8**)(self + 0xd4);
        child[0x8c] = (u8)flag;
        return;
    }
    if (flag == 0) return;
    u8* o = *(u8**)(self + 0x80);
    if (o == 0) return;
    if (o[0x16c] == 0) return;
    func_001B6C2C(child);
    func_001B6A48(*(u8**)(self + 0xd4));
    child = *(u8**)(self + 0xd4);
    child[0x94] = 1;
    child = *(u8**)(self + 0xd4);
    child[0x8c] = 1;
}
