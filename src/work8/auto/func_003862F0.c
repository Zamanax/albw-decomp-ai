typedef unsigned int u32;
typedef unsigned char u8;

extern u32 data_00709D28;
extern void func_004A3700(void*);
extern void func_004A9120(u32, void*);

void func_003862F0(char* self) {
    u32 z = 0;
    char* slot = self + 0x1bc;
    *(u8*)(self + 0x37) = z;
    void* obj = *(void**)slot;
    if (obj != 0) {
        if (*(u32*)((char*)obj + 0x1c) == *(u32*)(slot + 4)) {
            u32 f = *(u32*)((char*)obj + 0x3c);
            f = (f & ~0x44u) | 8;
            *(u32*)((char*)obj + 0x3c) = f;
            func_004A3700(obj);
        }
    }
    *(u8*)(self + 0x3a) = 0xff;
    if (*(u8*)(self + 0x34) != 0) {
        *(u8*)(self + 0x34) = z;
        func_004A9120(data_00709D28, self + 0xb4);
    }
}
