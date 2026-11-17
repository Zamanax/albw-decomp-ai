typedef unsigned int u32;
extern char ro_006CE070[];
extern void* func_004A1520(void* p);
typedef void (*VFn)(void*);
typedef struct { void* a; void* b; } VP;

void* func_0058E918(char* self) {
    char* base = self - 4;
    VP* p = (VP*)base;
    char* a = ro_006CE070;
    VP t = { a, a + 0x34 };
    *p = t;
    void* inner = *(void**)(self + 0x10);
    VFn fn = *(VFn*)(*(char**)inner + 0x14);
    fn(inner);
    return (char*)func_004A1520(base + 4) - 4;
}
