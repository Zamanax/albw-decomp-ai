typedef unsigned int u32;
typedef unsigned char u8;

extern void* data_00712588;
extern void func_002DF504(void*, char*);

void func_003AE7F4(char* self, const char* src) {
    u32* d = (u32*)(self + 0xcc);
    const u32* s = (const u32*)src;
    u32 t;
    t = s[1]; d[1] = t;
    t = s[2]; d[2] = t;
    t = s[3]; d[3] = t;
    t = s[4]; d[4] = t;
    t = s[5]; d[5] = t;
    t = s[6]; d[6] = t;
    t = s[7]; d[7] = t;
    t = s[8]; d[8] = t;
    t = s[9]; d[9] = t;
    t = s[10]; d[10] = t;
    t = s[12]; d[12] = t;
    u8* db = (u8*)d;
    const u8* sb = (const u8*)src;
    u8 b;
    b = sb[0x34]; db[0x34] = b;
    b = sb[0x35]; db[0x35] = b;
    b = sb[0x36]; db[0x36] = b;
    b = sb[0x37]; db[0x37] = b;
    b = sb[0x38]; db[0x38] = b;
    *(u32*)(self + 0x108) = s[15];
    void** vt = *(void***)self;
    ((void (*)(void*))vt[0x44 / 4])(self);
    *(u8*)(self + 0x10c) = 1;
    func_002DF504(data_00712588, self);
}
