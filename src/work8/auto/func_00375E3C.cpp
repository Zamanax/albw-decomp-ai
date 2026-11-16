typedef unsigned int u32;
extern "C" void func_004CF478(void*, u32, u32);
extern "C" void func_004D8A88(void*, u32);
extern "C" void func_0015133C(void*, void*);
extern "C" void func_00151150(void*, void*);
extern "C" void func_001512E8(void*);
extern "C" void func_003314F8(void);
extern u32 data_0070F440;
extern u32 data_00785AB8;

extern "C" void func_00375E3C(void* self) {
    char* p = (char*)self;
    {
        u32 buf[10];
        func_004CF478(*(void**)(p + 0x430), 0, 0);
        func_004D8A88(buf, data_0070F440 + *(u32*)(p + 0x3e8));
        func_0015133C((void*)*(u32*)(p + 0x434), buf);
    }
    func_00151150((void*)*(u32*)(p + 0x434), &data_00785AB8);
    func_001512E8((void*)*(u32*)(p + 0x434));
    func_003314F8();
}
