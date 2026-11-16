typedef unsigned int u32;
extern void* func_0056A244(void* p);

void* func_0041297C(void* self, void* p) {
    u32 z = 0;
    *(u32*)((char*)self + 0x0) = z;
    *(u32*)((char*)self + 0x4) = z;
    if (*(u32*)p != 0x44535743u) {
        return self;
    }
    u32 v = *(u32*)((char*)p + 8);
    if (v + 0xff000000u > 0x100u) {
        return self;
    }
    *(void**)self = p;
    void* a = p;
    void* q = func_0056A244(a);
    if (q == 0) {
        return self;
    }
    *(void**)((char*)self + 4) = (char*)q + 8;
    return self;
}
