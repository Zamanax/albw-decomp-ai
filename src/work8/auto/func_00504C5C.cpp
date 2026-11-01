typedef unsigned char u8;
typedef unsigned int u32;

extern "C" void* func_0010CEE0(u32, void*, u32);
extern "C" void* func_0010DA7C(void*, void*, u32);
extern "C" void* func_0050547C(void*);
extern "C" char ro_006F8164[];

struct G505420 { char _pad[8]; void* m8; void* mC; };
extern "C" G505420 data_0070BC20;

void* func_00504C5C(void* heap) {
    if (data_0070BC20.m8 != 0) return data_0070BC20.m8;
    void* p = func_0010CEE0(0x118, heap, 4);
    void* r;
    if (p == 0) {
        data_0070BC20.mC = p;
        r = 0;
    } else {
        void* hh = heap;
        u32 kk = 3;
        void* q = func_0010DA7C(p, hh, kk);
        *(void**)q = ro_006F8164;
        data_0070BC20.mC = q;
        r = func_0050547C(p);
    }
    data_0070BC20.m8 = r;
    return r;
}
