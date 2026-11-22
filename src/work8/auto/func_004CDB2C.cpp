typedef unsigned int u32;
typedef int s32;

extern "C" s32 func_0058080C(void* head, u32 target);
extern "C" void func_0010F1F8(void* node);

extern "C" u32 func_004CDB2C(char* self, char* p) {
    if (p == 0) return 0;
    s32 a = *(s32*)(p + 0x24);
    if (a == 0) a = *(s32*)(p + 0x20);
    if (a == 0) {
        s32 b = *(s32*)(p + 0x2c);
        if (b == 0) b = *(s32*)(p + 0x28);
        if (b == 0) return 0;
    }
    {
        void* vt = *(void**)p;
        void (*fp)(void*) = *(void (**)(void*))((char*)vt + 0x24);
        fp(p);
    }
    {
        char* q = self + 0x14;
        s32 r = func_0058080C(q, *(u32*)(self + 0x20) + (u32)p);
        if (r >= 0) {
            func_0010F1F8((char*)(*(u32*)(self + 0x20) + (u32)p));
            *(s32*)(self + 0x1c) = *(s32*)(self + 0x1c) - 1;
        }
    }
    {
        char* q = self + 0x24;
        s32 r = func_0058080C(q, *(u32*)(self + 0x30) + (u32)p);
        if (r >= 0) {
            func_0010F1F8((char*)(*(u32*)(self + 0x30) + (u32)p));
            *(s32*)(self + 0x2c) = *(s32*)(self + 0x2c) - 1;
        }
    }
    return 1;
}
