typedef unsigned char u8;
typedef unsigned int u32;

extern "C" void* func_0010CEE0(u32, void*, u32);
extern "C" void* func_0010DA7C(void*, void*, u32);
extern "C" void func_0010FD28(void*);
extern "C" char ro_006F50F8[];

struct G {
    void* m0;
    void* m4;
};

extern "C" G data_00715388;

void* func_0010D5C8(void* heap) {
    if (data_00715388.m0 == 0) {
        u8* p = (u8*)func_0010CEE0(0x20, heap, 4);
        u8* q = p + 0x10;
        if (q != 0) {
            void* hh = heap;
            u32 kk = 3;
            q = (u8*)func_0010DA7C(q, hh, kk);
            *(void**)q = ro_006F50F8;
        }
        data_00715388.m4 = q;
        void* res = p ? (func_0010FD28(p), (void*)p) : 0;
        data_00715388.m0 = res;
    }
    return data_00715388.m0;
}
