typedef unsigned char u8;
typedef unsigned int u32;
extern void* func_00412BB4(void*);
extern void* func_00412A3C(void*, int);
extern void func_00412C68(void*, void*);
void func_0040D864(void* self, int arg) {
    void* q = func_00412BB4(self);
    void * t0 = func_00412A3C(q, 6);
    u8* r = (u8*)t0;
    *(u32*)(r + 0xc) = *(u32*)((u8*)q + 0x184);
    r[4] = 0xb;
    void* (*fp)(void*) = *(void* (**)(void*))((u8*)(*(void**)self) + 0x20);
    *(void**)(r + 0x10) = fp(self);
    r[0x14] = (u32)arg;
    func_00412C68(q, r);
}
