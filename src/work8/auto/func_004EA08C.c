typedef unsigned char u8;
typedef unsigned int u32;

extern void func_001E6CE8(void* p);
extern void func_00689024(void* p);
extern void func_005382AC(void* a, void* b, void* c, u32 d);
extern void func_00297140(void* a, void* b);

void func_004EA08C(char* self, u8* p) {
    char s[0x4c];
    func_001E6CE8(*(void**)(self + 0x50));
    if (*p == 8) {
        func_00689024(s);
        func_005382AC(*(void**)(self + 0x50), s, p, 1);
        func_00297140(*(void**)(self + 0x4c), s);
    }
}
