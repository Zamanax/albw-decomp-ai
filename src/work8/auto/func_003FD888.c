typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern u32 func_003E6600(u8* p, u32 a, u32 b, u32 c);

void func_003FD888(u32* self, u8* p) {
    int i;
    u8* cur;
    self[0] = 0;
    self[1] = 0;
    self[2] = 0;
    self[3] = 0;
    if (func_003E6600(p, 0x4e414c46, 0x3000000, 1) == 0) {
        return;
    }
    self[0] = (u32)p;
    cur = p + *(u16*)(p + 6);
    i = 0;
    while (i < (int)*(u16*)(p + 0x10)) {
        u32 k = *(u32*)cur + 0xce979e90;
        if (k == 0) {
            self[3] = (u32)cur;
        } else if (k == 0x10000) {
            self[1] = (u32)cur;
        } else if (k == 0xc0000) {
            self[2] = (u32)cur;
        }
        cur = cur + *(u32*)(cur + 4);
        i++;
    }
}
