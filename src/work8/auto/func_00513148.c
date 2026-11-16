typedef unsigned int u32;
typedef unsigned char u8;
void func_0066B94C(void* p, u32 v);

void func_00513148(u8* self) {
    if (self[0x490] == 1) {
        u32 t = self[0x548];
        if (t == 3 || t == 6 || t == 7) {
            func_0066B94C(self + 0x48c, 4);
        } else if (t == 8) {
            func_0066B94C(self + 0x48c, 0xc);
        }
    }
}
