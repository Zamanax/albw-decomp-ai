typedef unsigned char u8;
typedef unsigned int u32;
inline void* operator new(unsigned int, void* p) throw() { return p; }
extern "C" void* func_0010CEE0(u32, void*, u32);
struct IDisposer { IDisposer(void* heap, int opt); virtual ~IDisposer(); u32 m4, m8, mc; };
struct Disposer : IDisposer { Disposer(void* heap) : IDisposer(heap, 3) {} virtual ~Disposer(); };
struct T4AB { u8 pad[0x10]; u32 m10, m14, m18, m1c, m20, m24, m28, m2c; T4AB() { m10 = 0; m14 = 0; m18 = 0; m1c = 0; m20 = 0; m24 = 0; m28 = 0; m2c = 0; } };
struct G { T4AB* m0; Disposer* m4; };
extern "C" G data_0070FB60;
T4AB* func_003614CC(void* heap) {
    if (data_0070FB60.m0 == 0) {
        u8* buf = (u8*)func_0010CEE0(sizeof(T4AB), heap, 4);
        data_0070FB60.m4 = new (buf) Disposer(heap);
        data_0070FB60.m0 = new (buf) T4AB;
    }
    return data_0070FB60.m0;
}
