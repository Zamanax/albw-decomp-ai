typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" char ro_006F7EEC[];
extern "C" void* func_00232540(void* p);

struct S { u16 a; u16 b; f32 c; u32 d; };

void* func_004A51FC(void* p) {
    void* r = func_00232540(p);
    u8* q = (u8*)r;
    *(void**)q = ro_006F7EEC;
    q += 0x20;
    S* s = (S*)q;
    s->a = 0;
    s->b = 0xffff;
    s->c = 0.0f;
    s->d = 0;
    return r;
}
