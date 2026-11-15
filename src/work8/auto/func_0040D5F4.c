typedef unsigned char u8;
typedef unsigned int u32;
extern void* func_00412BB4(void*);
extern void* func_00412A3C(void*, int);
extern void func_00412C68(void*, void*);
typedef void* (*VFn)(void*);

void func_0040D5F4(char* p, unsigned v) {
    char* q = (char*)(((((func_00412BB4(p))))));
    void * t6 = func_00412A3C(q, 6);
    char* r = (char*)t6;
    *(u32*)(r + 0xc) = *(u32*)(q + 0x184);
    r[4] = 0xa;
    *(void**)(0x10 + r) = ((VFn)(*(void**)(*(char**)p + 0x20)))(p);
    r[0x15] = v;
    func_00412C68(q, r);
}
