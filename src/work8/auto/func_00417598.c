typedef unsigned int u32;
extern void func_0041CA0C(void*);

void func_00417598(void* a, u32 mode, char* o) {
    if (mode == 0 || mode == 2) func_0041CA0C(a);
    void* obj = *(void**)(o + 0x12c);
    if (obj != 0) {
        void (**vt)(void*, void*) = *(void (***)(void*, void*))obj;
        vt[8](obj, a);
    }
    void* h = *(void**)(o + 0x130);
    if (h != a) {
        void* nx = *(void**)((char*)h + 0x1a4);
        if (nx == 0) return;
        void* cur = h;
        for (;;) {
            if (*(void**)((char*)cur + 0x1a4) == a) {
                *(void**)((char*)cur + 0x1a4) = *(void**)((char*)a + 0x1a4);
                return;
            }
            cur = *(void**)((char*)cur + 0x1a4);
            if (*(void**)((char*)cur + 0x1a4) == 0) return;
        }
    } else {
        *(void**)(o + 0x130) = *(void**)((char*)a + 0x1a4);
    }
}
