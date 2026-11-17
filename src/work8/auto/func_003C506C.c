typedef unsigned int u32;
typedef unsigned char u8;
extern void func_003842C0(void*, u32, u32, u32);
extern void func_003C5074(void*);

void func_003C506C(void* self) {
    char* p = (char*)self;
    func_003C5074(self);
    char* m48 = *(char**)(p + 0x48);
    *(u8*)(m48 + 0x936) = 1;
    m48 = *(char**)(p + 0x48);
    func_003842C0(m48 + 0x8c0, 0x32, 0xa, 1);
    void* vt = *(void**)self;
    void (*fp)(void*, u32, u32) = *(void (**)(void*, u32, u32))((char*)vt + 0x138);
    fp(self, 1, 1);
    void* vt2 = *(void**)self;
    void (*tail)(void*) = *(void (**)(void*))((char*)vt2 + 0xfc);
    tail(self);
}
