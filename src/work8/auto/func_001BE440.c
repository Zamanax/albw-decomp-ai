typedef unsigned int u32;
typedef unsigned char u8;
extern void* data_0070FB60;
extern void func_0014E2A0(void* self, u32 a, void* b, u32 c, u32 d, u32 e);

void func_001BE440(char* self) {
    char* obj = (char*)data_0070FB60;
    char* sub = *(char**)(obj + 0x28);
    u32 v = *(u32*)(sub + 4);
    char* s = *(char**)(self + 0x444);
    if (v != 0x3f800000) {
        *(u8*)(s + 0x44) = 0;
    } else {
        *(u8*)(s + 0x44) = 1;
    }
    func_0014E2A0(self, *(u32*)(self + 0x440), 0x458 + self, 0x100, 0, 0);
}
