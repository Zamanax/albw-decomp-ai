typedef signed char s8;
typedef unsigned int u32;

extern void func_0066E7A0(void*, s8);

void func_00479E24(void* self) {
    char* p = (char*)self;
    char* a = *(char**)(p + 0x1f4);
    s8 sa = *(s8*)(a + 0x3c);
    if ((u32)(sa - 1) > 5) {
        u32 z = 0;
        char* b = *(char**)(p + 0x1f8);
        s8 sb = *(s8*)(b + 0x3c);
        if ((u32)(sb - 1) > 5) {
            u32 f = *(u32*)(p + 0x298);
            if (f == 0) {
                func_0066E7A0(p + 0xcc, 0);
            } else {
                *(u32*)(p + 0x298) = z;
            }
        }
    }
}
