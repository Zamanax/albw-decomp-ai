typedef unsigned char u8;
typedef unsigned int u32;
inline void* operator new(unsigned int, void* p) throw() { return p; }
struct NoThrowT {};
void* operator new(unsigned int, NoThrowT) throw();
extern "C" void* func_0010CEE0(u32, void*, u32);
struct IDisposer { IDisposer(void* heap, int opt); virtual ~IDisposer(); u32 m4, m8, mc; };
struct Disposer : IDisposer { Disposer(void* heap) : IDisposer(heap, 3) {} virtual ~Disposer(); };
struct T4AB;
struct Obj434 { Obj434(T4AB* owner); char pad[0x434]; };
struct T4AB { u8 pad[0x10]; Obj434* m10; u32 m14; T4AB() { NoThrowT nt; m10 = new (nt) Obj434(this); m14 = 0; } };
struct G { T4AB* m0; Disposer* m4; };
extern "C" G data_00711010;
T4AB* func_005183CC(void* heap) {
    if (data_00711010.m0 == 0) {
        u8* buf = (u8*)func_0010CEE0(sizeof(T4AB), heap, 4);
        data_00711010.m4 = new (buf) Disposer(heap);
        data_00711010.m0 = new (buf) T4AB;
    }
    return data_00711010.m0;
}
