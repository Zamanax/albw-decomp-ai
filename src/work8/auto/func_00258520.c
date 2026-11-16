typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
extern u32 func_0057D86C(void* p);
extern void func_0040D80C(void* p);
extern void func_00257528(void* self, s32 v);

void func_00258520(char* self, s32 r1) {
    if (*(u8*)(self + 0x64) != 0) return;
    u32 f = *(u8*)(self + 0x68);
    if (f == 0) f = *(u8*)(self + 0x69);
    if (f != 0) {
        if (r1 <= 0) r1 = 1;
    } else {
        if (r1 <= 0) {
            char* q = self;
            if (func_0057D86C(q + 0xc) == 0) return;
            void* p = *(void**)(q + 0xc);
            if (p) func_0040D80C(p);
            p = *(void**)(q + 0xc);
            s32 v = p ? *(s32*)((char*)p + 0xac) : -1;
            func_00257528(q, v);
            return;
        }
    }
    *(s32*)(self + 0x44) = r1;
}
