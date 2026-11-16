typedef unsigned int u32;
typedef u32 (*VFn)(void* self);
extern u32 func_00569578(void* a, u32 b, void* c, u32 d);

u32 func_001B6E54(char* self, int a1, char* list, u32 a3)
{
    u32 ret = 0;
    void** cur = *(void***)(self + 0x20);
    void** end = cur + *(u32*)(self + 0x18);
    if (cur == end) return ret;
    for (; cur != end; cur++) {
        char* sentinel = list + 0x10;
        char* node = *(char**)(list + 0x10);
        while (node != sentinel) {
            void* elem = *(void**)(node + 8);
            void* m = *(void**)((char*)*cur + 0x44);
            if ((((VFn)(*(void***)elem)[2])(elem)) == (((VFn)(*(void***)m)[2])(m))) {
                ret = func_00569578(*cur, a1, elem, a3);
                if (ret != 0) break;
            }
            node = *(char**)node;
        }
    }
    return ret;
}
