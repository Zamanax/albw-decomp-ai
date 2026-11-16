extern void* func_0041F7CC(void*);
extern void func_0041F7DC(void);

void func_0023248C(char* self, char* a, unsigned int b) {
    char* p = *(char**)(self + 0x1c);
    if (p == 0) return;
    unsigned int flags = *(unsigned int*)(self + 0x18);
    if (flags & 4) return;
    if (flags & 0x10) return;
    if (*(unsigned int*)(p + 0x10) != 0) return;
    char* q = *(char**)p;
    char* ap = a;
    unsigned int bb = b;
    if (q == 0) return;
    void* r = func_0041F7CC(p);
    void (*fp)(void*, void*, void*, unsigned int) =
        *(void (**)(void*, void*, void*, unsigned int))(*(char**)ap + 0x24);
    fp(ap, r, q, bb);
    func_0041F7DC();
}
