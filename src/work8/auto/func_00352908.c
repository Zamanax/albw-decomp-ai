typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern void func_004A20B4(void* a, void* b);

typedef struct { u32 a, b, c; } Tri12;

void func_00352908(char* self, char* src) {
    if (*(u32*)(self + 0x20) == 0) return;
    if (*(u32*)(src + 0xc) != 0) {
        char* old = *(char**)(self + 0x2c);
        if (old != 0) *(u32*)(old + 0xa4) = 0;
        char* n = *(char**)(src + 0xc);
        *(char**)(self + 0x2c) = n;
        u32 w = *(u32*)(n + 4);
        *(u16*)(self + 0x34) = (u16)w;
        *(char**)(n + 0xa4) = self;
    }
    if (*(u32*)(src + 0x10) != 0) {
        char* old = *(char**)(self + 0x30);
        if (old != 0) *(u32*)(old + 0x10) = 0;
        char* m = *(char**)(src + 0x10);
        *(char**)(self + 0x30) = m;
        *(u16*)(self + 0x36) = *(u8*)(*(char**)(src + 0x10) + 6);
        *(char**)(m + 0x10) = self;
    }
    Tri12 t = *(Tri12*)src;
    func_004A20B4(*(void**)(self + 0x20), &t);
}
