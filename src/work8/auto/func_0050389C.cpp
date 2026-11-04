typedef unsigned int u32;
typedef int s32;

struct Self {
    u32 pad[9];
    void* m24;
};

extern "C" u32 func_00404500(Self* self);
extern "C" void* func_00404138(u32 size, u32 align);
extern "C" void* func_00404C78(void* p);
extern "C" char ro_006EE450[];

extern "C" void* func_0050389C(Self* self, u32, u32 a, u32 b) {
    u32 a5 = a;
    u32 r8 = func_00404500(self);
    u32* p = (u32*)func_00404138(0x34, 4);
    if (p) {
        for (s32 i = 0; i < 13; i++) p[i] = 0;
        p = (u32*)func_00404C78(p);
        *(void**)p = ro_006EE450;
    }
    void** obj = (void**)p;
    typedef void (*VCall)(void*, u32, void*, u32, u32);
    ((VCall)((void**)*obj)[14])(obj, r8, self->m24, b, a5);
    return obj;
}
